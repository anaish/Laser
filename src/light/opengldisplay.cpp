#include "opengldisplay.hpp"

GLuint scene_list = 0;

GLfloat LightAmbient[]= { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[]= { 0.0f, 0.0f, 15.0f, 1.0f };

// current rotation angle
static float rotationAngle = 0.f;
static float rotationX = 0.f;
static float rotationY = 0.f;
static float rotationZ = 0.f;



/**
An opengl implementation of the Display interface.
**/
OpenGlDisplay :: OpenGlDisplay(){

}


/**
Initialises the Open GL context.
Should only be called once.
**/
void OpenGlDisplay::init(PConfig config){
	
	LOG(ERROR) << "Initialising Model Importer";

	this->modelImporter = PModelImporter(new AssimpModelImporter());
	this->modelImporter->init(config);

	LOG(ERROR) << "Initialising OpenGL";

	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        	LOG(ERROR) << "Unable to init SDL";
    }
	
	int displayWidth = config->getInt("display","width");
	int displayHeight = config->getInt("display","height");

	screen = SDL_SetVideoMode(displayWidth,displayHeight , 32, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL);

	if(screen == NULL) {
		LOG(ERROR) << "Unable to init screen";
	}

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,        8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,      8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,       8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,      8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,      16);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,     32);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,  8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,    8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE,    8);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,  1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,  2);

	glViewport(0, 0, displayWidth, displayHeight);
	glOrtho(0, displayWidth, displayHeight, 0, 1, -1);

    glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);		 // Enables Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);				// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);		// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);			// The Type Of Depth Test To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculation

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);    // Uses default lighting parameters
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_NORMALIZE);
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);
	glEnable(GL_LIGHT1);


} 

/**
Renders the display.

TODO The game loop calls this every time - do we want this, or should we only render when we need to?
The ultimate goal really is to not have the display affect the performance of the game - even if
we have to skip frames to achieve it.
**/
void OpenGlDisplay::OnRender(){

	 this->render();

}

void OpenGlDisplay::rotateScene(float angle, float x, float y, float z){

	rotationAngle += angle;
	rotationX = x;
	rotationY = y;
	rotationZ = z;

}


// ----------------------------------------------------------------------------
void OpenGlDisplay::render(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	// scale the asset to fit into our view
	float tmp;
	tmp = this->modelImporter->scene_max.x-this->modelImporter->scene_min.x;
	tmp = aisgl_max(this->modelImporter->scene_max.y - this->modelImporter->scene_min.y,tmp);
	tmp = aisgl_max(this->modelImporter->scene_max.z - this->modelImporter->scene_min.z,tmp);
	tmp = 1.f / tmp;
	glScalef(tmp, tmp, tmp);

     // center the model
	glTranslatef(-(this->modelImporter->scene_center.x),
			-(this->modelImporter->scene_center.y),
			-this->modelImporter->scene_center.z);

	// rotate it around the y axis
	/*TODO at the moment it only rotates when you do some SDL event (like click the mouse or
	 * press a key) We really need to look at moving the object in a more generic way
	 * like using a physics engine, and have it react to user input (and other game objects)
	*/
	glRotatef(rotationAngle,rotationX,rotationY,rotationZ);

        // if the display list has not been made yet, create a new one and
        // fill it with scene contents
	if(scene_list == 0) {
	    scene_list = glGenLists(1);
	    glNewList(scene_list, GL_COMPILE);
            // now begin at the root node of the imported data and traverse
            // the scenegraph by multiplying subsequent local transforms
            // together on GL's matrix stack.
	    const aiScene* scene = modelImporter->getScene();
	    recursive_render(scene, scene->mRootNode);
	    glEndList();
	}

	glCallList(scene_list);

	SDL_GL_SwapBuffers();
}


// ----------------------------------------------------------------------------
void OpenGlDisplay::recursive_render (const struct aiScene *sc, const struct aiNode* nd)
{
	unsigned int i;
	unsigned int n = 0, t;
	struct aiMatrix4x4 m = nd->mTransformation;

	// update transform
	aiTransposeMatrix4(&m);
	glPushMatrix();
	glMultMatrixf((float*)&m);

	// draw all meshes assigned to this node
    const aiScene* scene = modelImporter->getScene();

	for (; n < nd->mNumMeshes; ++n) {
		const struct aiMesh* mesh = scene->mMeshes[nd->mMeshes[n]];

		apply_material(sc->mMaterials[mesh->mMaterialIndex]);

		if(mesh->mNormals == NULL) {
			glDisable(GL_LIGHTING);
		} else {
			glEnable(GL_LIGHTING);
		}

		if(mesh->mColors[0] != NULL) {
			glEnable(GL_COLOR_MATERIAL);
		} else {
			glDisable(GL_COLOR_MATERIAL);
		}

		for (t = 0; t < mesh->mNumFaces; ++t) {
			const struct aiFace* face = &mesh->mFaces[t];
			GLenum face_mode;

			switch(face->mNumIndices) {
				case 1: face_mode = GL_POINTS; break;
				case 2: face_mode = GL_LINES; break;
				case 3: face_mode = GL_TRIANGLES; break;
				default: face_mode = GL_POLYGON; break;
			}

			glBegin(face_mode);
			for(i = 0; i < face->mNumIndices; i++) {
				int index = face->mIndices[i];
				if(mesh->mColors[0] != NULL)
					color4f(&mesh->mColors[0][index]);
				if(mesh->mNormals != NULL)
					glNormal3fv(&mesh->mNormals[index].x);
				glVertex3fv(&mesh->mVertices[index].x);
			}

			glEnd();
		}

	}

	// draw all children
	for (n = 0; n < nd->mNumChildren; ++n) {
		recursive_render(sc, nd->mChildren[n]);
	}

	glPopMatrix();
}

/**
 * Applies the material
 */
void OpenGlDisplay::apply_material(const struct aiMaterial *mtl){

	float c[4];

	GLenum fill_mode;
	unsigned int ret1, ret2;
	struct aiColor4D diffuse;
	struct aiColor4D specular;
	struct aiColor4D ambient;
	struct aiColor4D emission;
	float shininess, strength;
	int two_sided;
	int wireframe;
	unsigned int max;

	set_float4(c, 0.8f, 0.8f, 0.8f, 1.0f);
	if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_DIFFUSE, &diffuse))
		color4_to_float4(&diffuse, c);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, c);

	set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
	if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_SPECULAR, &specular))
		color4_to_float4(&specular, c);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);

	set_float4(c, 0.2f, 0.2f, 0.2f, 1.0f);
	if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_AMBIENT, &ambient))
		color4_to_float4(&ambient, c);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, c);

	set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
	if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_EMISSIVE, &emission))
		color4_to_float4(&emission, c);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, c);

	max = 1;
	ret1 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS, &shininess, &max);
	max = 1;
	ret2 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS_STRENGTH, &strength, &max);
	if((ret1 == AI_SUCCESS) && (ret2 == AI_SUCCESS))
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess * strength);
	else {
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0f);
		set_float4(c, 0.0f, 0.0f, 0.0f, 0.0f);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);
	}

	max = 1;
	if(AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_ENABLE_WIREFRAME, &wireframe, &max))
		fill_mode = wireframe ? GL_LINE : GL_FILL;
	else
		fill_mode = GL_FILL;
	glPolygonMode(GL_FRONT_AND_BACK, fill_mode);

	max = 1;
	if((AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_TWOSIDED, &two_sided, &max)) && two_sided)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);


}

// Can't send color down as a pointer to aiColor4D because AI colors are ABGR.
void OpenGlDisplay::color4f(const struct aiColor4D *color)
{
	glColor4f(color->r, color->g, color->b, color->a);
}


// ----------------------------------------------------------------------------

void OpenGlDisplay::color4_to_float4(const struct aiColor4D *c, float f[4])
{
	f[0] = c->r;
	f[1] = c->g;
	f[2] = c->b;
	f[3] = c->a;
}

// ----------------------------------------------------------------------------

void OpenGlDisplay::set_float4(float f[4], float a, float b, float c, float d)
{
	f[0] = a;
	f[1] = b;
	f[2] = c;
	f[3] = d;
}

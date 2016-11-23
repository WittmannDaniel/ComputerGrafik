// Jonathan Siefert			Assingments Computergraphic
// Daniel Wittmann

#include "application_solar.hpp"
#include "launcher.hpp"
#include "texture_loader.hpp"


#include "utils.hpp"
#include "shader_loader.hpp"
#include "model_loader.hpp"

#include <glbinding/gl/gl.h>
// use gl definitions from glbinding 
using namespace gl;

//dont load gl bindings from glfw
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <random>
#include <cstdlib>
#include <string>

std::vector<texture_object> texture_objects;


// texture_loader::file(m_resource_path + "textures/sunmap.png")

/*// initialize all planets
planet sun{ "sun"    , 0.0f, 0.0f, 0.7f, false, texture_loader::file(m_resource_path + "texture/sunmap.png" ) };
planet mercury{ "mercury", 1.0f , 365 / 88.0f, 0.05f, false, 0.5f, 0.5f, 0.5f };
planet venus{ "venus"  , 2.0f , 365 / 225.0f, 0.2f, false, 0.5f, 0.5f, 1.0f };
planet earth{ "earth"  , 3.0f , 1.0f , 0.15f, false, 0.0f, 0.0f, 1.0f };
planet mars{ "mars"   , 3.5f , 365 / 687.0f   , 0.1f, false, 1.0f, 0.0f, 0.0f };
planet jupiter{ "jupiter", 4.0f , 365 / 4329.f, 0.35f, false, 0.5f, 0.5f, 0.7f };
planet saturn{ "saturn" , 5.0f , 365 / 1751.0f, 0.2f, false, 0.7f, 0.7f, 0.4f };
planet uranus{ "uranus" , 6.0f , 365 / 30664.0f , 0.2f, false, 0.5f, 0.5f, 0.7f };
planet neptune{ "neptune", 6.5f , 365 / 60148.0f , 0.15f, false, 0.5f, 0.5f, 1.0f };
planet moon{ "moon"   , 0.3f , 1.0f ,0.05f, true, 0.5f, 0.5f, 0.5f };*/

std::vector<planet>planets; 
std::vector<texture_object> textures;


ApplicationSolar::ApplicationSolar(std::string const& resource_path)
 :Application{resource_path}
 ,planet_object{}
 ,stars{}
 ,stars_object{}
 

{
	// initialize all planets
	planet skybox{ "skybox"    , 0.0f, 0.0f, 50.0f, false, texture_loader::file(m_resource_path + "textures/skybox.png") };
	planet sun{ "sun"    , 0.0f, 0.0f, 0.7f, false, texture_loader::file(m_resource_path + "textures/sunmap.png") };
	planet mercury{ "mercury", 1.0f , 365 / 88.0f, 0.05f, false, texture_loader::file(m_resource_path + "textures/mercurymap.png") };
	planet venus{ "venus"  , 2.0f , 365 / 225.0f, 0.2f, false, texture_loader::file(m_resource_path + "textures/venusmap.png") };
	planet earth{ "earth"  , 3.0f , 1.0f , 0.15f, false, texture_loader::file(m_resource_path + "textures/earthmap.png") };
	planet mars{ "mars"   , 3.5f , 365 / 687.0f   , 0.1f, false, texture_loader::file(m_resource_path + "textures/marsmap.png") };
	planet jupiter{ "jupiter", 4.0f , 365 / 4329.f, 0.35f, false, texture_loader::file(m_resource_path + "textures/jupitermap.png") };
	planet saturn{ "saturn" , 5.0f , 365 / 1751.0f, 0.2f, false, texture_loader::file(m_resource_path + "textures/saturnmap.png") };
	planet uranus{ "uranus" , 6.0f , 365 / 30664.0f , 0.2f, false, texture_loader::file(m_resource_path + "textures/uranusmap.png") };
	planet neptune{ "neptune", 6.5f , 365 / 60148.0f , 0.15f, false, texture_loader::file(m_resource_path + "textures/neptunemap.png") };
	planet moon{ "moon"   , 0.3f , 1.0f ,0.05f, true, texture_loader::file(m_resource_path + "textures/moonmap.png") };

	planets = { sun, mercury, venus, earth, mars, jupiter, saturn, uranus, neptune, moon, skybox };

  initializeGeometry();
  initializeShaderPrograms();
  initializeTextures();
}

void ApplicationSolar::upload_planet_transforms(planet const& planet, texture_object const& tex_object) const {
	// Planet -- std::string name; float distance; float speed; float size; bool is_moon;

	glm::fmat4 model_matrix = glm::fmat4{};

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(tex_object.target, tex_object.handle);

	glUniform1i(glGetUniformLocation(m_shaders.at("planet").handle, "ColorTex"), tex_object.handle);
	
	if (planet.is_moon == true)
	{
		// translation for moon to fly aroud earth -- planets[3] -> earth
		model_matrix = glm::rotate(model_matrix, planets[3].speed * float(glfwGetTime()), glm::fvec3{ 0.0f, 1.0f, 0.0f });
		model_matrix = glm::translate(model_matrix, glm::fvec3{ 0.0f, 0.0f, planets[3].distance });
		model_matrix = glm::rotate(model_matrix, planet.speed * float(glfwGetTime()), glm::fvec3{ 1.0f, 0.0f, 1.0f });
		model_matrix = glm::translate(model_matrix, glm::fvec3{ 0.0f, 0.0f, planet.distance });
		
		model_matrix = glm::scale(model_matrix, glm::fvec3{ planet.size });
		glUniformMatrix4fv(m_shaders.at("planet").u_locs.at("ModelMatrix"),
			1, GL_FALSE, glm::value_ptr(model_matrix));
	}

	else
	{
		// translation for planets
		model_matrix = glm::rotate(glm::fmat4{}, planet.speed * float(glfwGetTime()), glm::fvec3{ 0.0f, 1.0f, 0.0f });
		model_matrix = glm::translate(model_matrix, glm::fvec3{ 0.0f, 0.0f, planet.distance });
		model_matrix = glm::scale(model_matrix, glm::fvec3{ planet.size });
		glUniformMatrix4fv(m_shaders.at("planet").u_locs.at("ModelMatrix"),
			1, GL_FALSE, glm::value_ptr(model_matrix));
	}

	// extra matrix for normal transformation to keep them orthogonal to surface
	glm::fmat4 normal_matrix = glm::inverseTranspose(glm::inverse(m_view_transform) * model_matrix);
	glUniformMatrix4fv(m_shaders.at("planet").u_locs.at("NormalMatrix"),
		1, GL_FALSE, glm::value_ptr(normal_matrix));

	//upload planet uniform
	glUniform3f(glGetUniformLocation(m_shaders.at("planet").handle, "planet_rgb"),
		planet.rgb_color[0],
		planet.rgb_color[1],
		planet.rgb_color[2]);
};



void ApplicationSolar::render() const {
	// bind shader to upload uniforms
	//glUseProgram(m_shaders.at("planet").handle);

	//render stars  
	glUseProgram(m_shaders.at("star").handle);

	//bind VAO of geometry
	glBindVertexArray(stars_object.vertex_AO);
	//draw geometry
	glDrawArrays(stars_object.draw_mode, 0, stars_object.num_elements / 6);


	// for loop over container of planets
	glUseProgram(m_shaders.at("planet").handle);

	std::vector<texture_object>::iterator j = textures.begin();
	for (std::vector<planet>::iterator i = planets.begin(); i != planets.end(); ++i)
	{
			upload_planet_transforms(*i, *j);

			// bind the VAO to draw
			glBindVertexArray(planet_object.vertex_AO);

			// draw bound vertex array using bound shader
			glDrawElements(planet_object.draw_mode, planet_object.num_elements, model::INDEX.type, NULL);

			++j;
	}


}

void ApplicationSolar::updateView() {
  // vertices are transformed in camera space, so camera transform must be inverted
  glm::fmat4 view_matrix = glm::inverse(m_view_transform);

  // upload matrix to gpu
  glUniformMatrix4fv(m_shaders.at("planet").u_locs.at("ViewMatrix"),
                     1, GL_FALSE, glm::value_ptr(view_matrix));


  // stars shader
  glUseProgram(m_shaders.at("star").handle);
  glUniformMatrix4fv(m_shaders.at("star").u_locs.at("ViewMatrix"),
					 1, GL_FALSE, glm::value_ptr(view_matrix));

  // return to planet shader
  glUseProgram(m_shaders.at("planet").handle);
}

void ApplicationSolar::updateProjection() {
  // upload matrix to gpu
  glUniformMatrix4fv(m_shaders.at("planet").u_locs.at("ProjectionMatrix"),
                     1, GL_FALSE, glm::value_ptr(m_view_projection));


  glUseProgram(m_shaders.at("star").handle);
  glUniformMatrix4fv(m_shaders.at("star").u_locs.at("ProjectionMatrix"),
					 1, GL_FALSE, glm::value_ptr(m_view_projection));

  glUseProgram(m_shaders.at("planet").handle);

}

// update uniform locations
void ApplicationSolar::uploadUniforms() {
  updateUniformLocations();
  
  // bind new shader
  glUseProgram(m_shaders.at("planet").handle);
  
  updateView();
  updateProjection();
}

// handle key input
void ApplicationSolar::keyCallback(int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_W && action == GLFW_PRESS) {
    m_view_transform = glm::translate(m_view_transform, glm::fvec3{0.0f, 0.0f, -0.1f});
    updateView();
  }
  else if (key == GLFW_KEY_S && action == GLFW_PRESS) {
    m_view_transform = glm::translate(m_view_transform, glm::fvec3{0.0f, 0.0f, 0.1f});
    updateView();
  }
}

//handle delta mouse movement input
void ApplicationSolar::mouseCallback(double pos_x, double pos_y) {
  // mouse handling
}

// load shader programs
void ApplicationSolar::initializeShaderPrograms() {
  // store shader program objects in container
  m_shaders.emplace("planet", shader_program{m_resource_path + "shaders/simple.vert",
                                           m_resource_path + "shaders/simple.frag"});
  // request uniform locations for shader program
  m_shaders.at("planet").u_locs["NormalMatrix"] = -1;
  m_shaders.at("planet").u_locs["ModelMatrix"] = -1;
  m_shaders.at("planet").u_locs["ViewMatrix"] = -1;
  m_shaders.at("planet").u_locs["ProjectionMatrix"] = -1;

  m_shaders.emplace("star", shader_program{m_resource_path + "shaders/stars.vert",
										  m_resource_path + "shaders/stars.frag" });
  //m_shaders.at("star").u_locs["ModelMatrix"] = 1;
  m_shaders.at("star").u_locs["ViewMatrix"] = -1;
  m_shaders.at("star").u_locs["ProjectionMatrix"] = -1;
}

// load models
void ApplicationSolar::initializeGeometry() {
  model planet_model = model_loader::obj(m_resource_path + "models/sphere.obj", model::NORMAL | model::TEXCOORD);

  // generate vertex array object
  glGenVertexArrays(1, &planet_object.vertex_AO);
  // bind the array for attaching buffers
  glBindVertexArray(planet_object.vertex_AO);

  // generate generic buffer
  glGenBuffers(1, &planet_object.vertex_BO);
  // bind this as an vertex array buffer containing all attributes
  glBindBuffer(GL_ARRAY_BUFFER, planet_object.vertex_BO);
  // configure currently bound array buffer
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * planet_model.data.size(), planet_model.data.data(), GL_STATIC_DRAW);

  // activate first attribute on gpu
  glEnableVertexAttribArray(0);
  // first attribute is 3 floats with no offset & stride
  glVertexAttribPointer(0, model::POSITION.components, model::POSITION.type, GL_FALSE, planet_model.vertex_bytes, planet_model.offsets[model::POSITION]);
  // activate second attribute on gpu
  glEnableVertexAttribArray(1);
  // second attribute is 3 floats with no offset & stride
  glVertexAttribPointer(1, model::NORMAL.components, model::NORMAL.type, GL_FALSE, planet_model.vertex_bytes, planet_model.offsets[model::NORMAL]);
  
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, model::TEXCOORD.components, model::TEXCOORD.type, GL_FALSE, planet_model.vertex_bytes, planet_model.offsets[model::TEXCOORD]);
  
  // generate generic buffer
  glGenBuffers(1, &planet_object.element_BO);
  // bind this as an vertex array buffer containing all attributes
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, planet_object.element_BO);
  // configure currently bound array buffer
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, model::INDEX.size * planet_model.indices.size(), planet_model.indices.data(), GL_STATIC_DRAW);

  // store type of primitive to draw
  planet_object.draw_mode = GL_TRIANGLES;
  // transfer number of indices to model object 
  planet_object.num_elements = GLsizei(planet_model.indices.size());

  initializeTextures();

  //initialization stars
  
  for (unsigned i = 0; i < 5000; ++i) {
	  for (unsigned j = 0; j < 3; ++j) { // position
		  stars.push_back(static_cast <float>(rand() % 201 - 100));
	  }
	  for (int j = 0; j < 3; ++j) { // color
		  stars.push_back(float(static_cast <float> (rand()) / static_cast <float> (RAND_MAX)));
	  }
  }


  glGenVertexArrays(1, &stars_object.vertex_AO);
  glBindVertexArray(stars_object.vertex_AO);

  glGenBuffers(1, &stars_object.vertex_BO);
  glBindBuffer(GL_ARRAY_BUFFER, stars_object.vertex_BO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * stars.size(), stars.data(), GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, NULL); 
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (GLvoid*)uintptr_t(sizeof(float) * 3));

  stars_object.draw_mode = GL_POINTS;
  stars_object.num_elements = GLsizei(5000);
}

ApplicationSolar::~ApplicationSolar() {
  glDeleteBuffers(1, &planet_object.vertex_BO);
  glDeleteBuffers(1, &planet_object.element_BO);
  glDeleteVertexArrays(1, &planet_object.vertex_AO);

  glDeleteBuffers(1, &stars_object.vertex_BO);
  glDeleteBuffers(1, &stars_object.element_BO);
  glDeleteVertexArrays(1, &stars_object.vertex_AO);
}


void ApplicationSolar::initializeTextures() {
	
	for (int i = 0; i < planets.size(); i++)
	{
		textures.push_back(utils::create_texture_object(planets[i].texture));
	} 
}


// exe entry point
int main(int argc, char* argv[]) {
  Launcher::run<ApplicationSolar>(argc, argv);
}
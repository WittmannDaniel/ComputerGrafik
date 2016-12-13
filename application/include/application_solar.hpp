#ifndef APPLICATION_SOLAR_HPP
#define APPLICATION_SOLAR_HPP

#include "application.hpp"
#include "model.hpp"
#include "structs.hpp"
#include "planet.hpp"
#include "framebuffer.hpp"


// gpu representation of model
class ApplicationSolar : public Application {
 public:
  // allocate and initialize objects
  ApplicationSolar(std::string const& resource_path);
  // free allocated objects
  ~ApplicationSolar();

  // update uniform locations and values
  void uploadUniforms();
  // update projection matrix
  void updateProjection();
  // react to key input
  void keyCallback(int key, int scancode, int action, int mods);
  //handle delta mouse movement input
  void mouseCallback(double pos_x, double pos_y);

  void upload_planet_transforms(planet const& planet, texture_object const& tex_object) const;

  // draw all objects
  void render() const;

 protected:
  void initializeShaderPrograms();
  void initializeGeometry();
  void updateView();
  void initializeTextures();
  void renderingQuad() const;

  void rendbuffer();
  void framebuffer();
  void screenQuad();



  
  std::vector<float> stars;
  model_object stars_object;
 
 
  GLuint tex_handle;


  // cpu representation of model
  model_object planet_object;
  model_object quad_object;
};

#endif
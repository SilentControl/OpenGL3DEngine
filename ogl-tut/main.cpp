#include <iostream>
#include "GL\glew.h"
#include "display.h"
#include "mesh.h"
#include "texture.h"
#include "shader.h"
#include "entity.h"
#include "renderer.h"
#include "light.h"
#include "objw_loader.h"
#include "masterRenderer.h"
#include "terrainTexturePack.h"
#include <cstdlib>
#include <ctime>

#define WIDTH 800
#define HEIGHT 600

int main(int argc, char* argv[])
{
	Display display(800, 600, "Hello world!");
	int frame_time = (int)((1.0 / display.FPS) * 1000);
	std::cout << "Frame time is: " << frame_time << " ms.\n";
	int start_time;
	int end_time;

	srand(time(NULL));

	/*Vertex vertices[] = {	Vertex(glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec2(0.0, 0.0)),
							Vertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0.0, 1.0)),
							Vertex(glm::vec3(0.5f, -0.5f, 0.0), glm::vec2(1.0, 1.0)),
							Vertex(glm::vec3(0.5f, 0.5f, 0.0f), glm::vec2(1.0, 0.0))	};*/
	/*Vertex vertices[] = {
		Vertex(glm::vec3(-1.0, -1.0, 1.0), glm::vec2(0.0, 0.0)),
		Vertex(glm::vec3(1.0, -1.0, 1.0), glm::vec2(0.0, 1.0)),
		Vertex(glm::vec3(1.0, 1.0, 1.0), glm::vec2(1.0, 1.0)),
		Vertex(glm::vec3(-1.0, 1.0, 1.0), glm::vec2(1.0, 0.0)),

		Vertex(glm::vec3(-1.0, -1.0, -1.0), glm::vec2(0.0, 0.0)),
		Vertex(glm::vec3(1.0, -1.0, -1.0), glm::vec2(0.0, 1.0)),
		Vertex(glm::vec3(1.0, 1.0, -1.0), glm::vec2(1.0, 1.0)),
		Vertex(glm::vec3(-1.0, 1.0, -1.0), glm::vec2(1.0, 0.0)),
	}*/;

	/*Vertex vertices[] = {
		Vertex(glm::vec3(0.0, 0.0, 0.0), glm::vec2(0.0, 1.0)),
		Vertex(glm::vec3(0.5, 0.0, 0.0), glm::vec2(1.0, 1.0)),
		Vertex(glm::vec3(0.0, 0.5, 0.0), glm::vec2(0.0, 0.0)),

		Vertex(glm::vec3(0.5, 0.0, 0.0), glm::vec2(1.0, 1.0)),
		Vertex(glm::vec3(0.5, 0.5, 0.0), glm::vec2(1.0, 0.0)),
		Vertex(glm::vec3(0.0, 0.5, 0.0), glm::vec2(0.0, 0.0)),

		Vertex(glm::vec3(0.0, 0.0, 0.5), glm::vec2(0.0, 1.0)),
		Vertex(glm::vec3(0.5, 0.0, 0.5), glm::vec2(1.0, 1.0)),
		Vertex(glm::vec3(0.0, 0.5, 0.5), glm::vec2(0.0, 0.0)),

		Vertex(glm::vec3(0.5, 0.0, 0.5), glm::vec2(1.0, 1.0)),
		Vertex(glm::vec3(0.5, 0.5, 0.5), glm::vec2(1.0, 0.0)),
		Vertex(glm::vec3(0.0, 0.5, 0.5), glm::vec2(0.0, 0.0)),
	//
		Vertex(glm::vec3(0.0, 0.5, 0.0), glm::vec2(0.0, 1.0)),
		Vertex(glm::vec3(0.5, 0.5, 0.0), glm::vec2(1.0, 1.0)),
		Vertex(glm::vec3(0.0, 0.5, 0.5), glm::vec2(0.0, 0.0)),

		Vertex(glm::vec3(0.5, 0.5, 0.0), glm::vec2(1.0, 1.0)),
		Vertex(glm::vec3(0.5, 0.5, 0.5), glm::vec2(1.0, 0.0)),
		Vertex(glm::vec3(0.0, 0.5, 0.5), glm::vec2(0.0, 0.0)),

		Vertex(glm::vec3(0.5, 0.5, 2.0), glm::vec2(1.0, 1.0)),
		Vertex(glm::vec3(0.5, 0.5, 2.5), glm::vec2(1.0, 0.0)),
		Vertex(glm::vec3(0.0, 0.5, 2.5), glm::vec2(0.0, 0.0)),
	};*/

	//std::vector<unsigned int> interconnect = { 0, 1, 3, 3, 1, 2 }; 


	/*Vertex vertices[] = {	Vertex(glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec2(0.0, 0.0)),
	Vertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0.0, 1.0)),
	Vertex(glm::vec3(0.5f, -0.5f, 0.0), glm::vec2(1.0, 1.0)),
	Vertex(glm::vec3(0.5f, 0.5f, 0.0f), glm::vec2(1.0, 0.0))	};*/

	//std::vector<float> vertices_pos = { -0.5f, 0.5f, 0.0f, -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0, 0.5f, 0.5f, 0.0f };
	//std::vector<float> texture_pos = { 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0 };

	/*std::vector<unsigned int> interconnect = { 0, 1, 2,
		2, 3, 0,
		// top
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// bottom
		4, 0, 3,
		3, 7, 4,
		// left
		4, 5, 1,
		1, 0, 4,
		// right
		3, 2, 6,
		6, 7, 3, };

	std::vector<float> vertices_pos = { -1.0, -1.0, 1.0,
		1.0, -1.0, 1.0,
		1.0, 1.0, 1.0,
		-1.0, 1.0, 1.0,
		// back
		-1.0, -1.0, -1.0,
		1.0, -1.0, -1.0,
		1.0, 1.0, -1.0,
		-1.0, 1.0, -1.0};

	std::vector<float> texture_pos;
	for (int i = 0; i < 16; i++)
		texture_pos.push_back(0.5f);*/

	Shader shader(".//res//");
	Renderer renderer(&shader);

	std::vector<float> vertices_pos;
	std::vector<float> texture_pos;
	std::vector<float> normals;
	std::vector<unsigned int> interconnect;

	load_obj(std::string(".//res//tree.obj"), vertices_pos, texture_pos, normals, interconnect);

	Mesh *mesh;
	mesh = new Mesh(vertices_pos, texture_pos, normals, interconnect);

	Texture texture(".//res//dragon.png", false);
	Entity *entity = new Entity(mesh, &texture, glm::vec3(0, 0, -16));
	entity->setLightVars(0.5, 1000.0);

	vertices_pos.clear();
	texture_pos.clear();
	normals.clear();
	interconnect.clear();

	load_obj(std::string(".//res//tree.obj"), vertices_pos, texture_pos, normals, interconnect);
	Texture grass(".//res//grass.png", false);
	Mesh *mesh3 = new Mesh(vertices_pos, texture_pos, normals, interconnect);
	Texture texture2(".//res//tree.png", false);
	Entity *entity3 = new Entity(mesh3, &texture2, glm::vec3(3, 0, -16));
	entity3->setLightVars(0.0, 0.0);

	Mesh *mesh4 = new Mesh(vertices_pos, texture_pos, normals, interconnect);
	Entity *entity4 = new Entity(mesh4, &grass, glm::vec3(-1, 0, -16));
	entity4->setLightVars(0.0, 0.0);
	//std::vector<float> vertices_pos2;
	//std::vector<float> texture_pos2;
	//std::vector<float> normals2;
	//std::vector<unsigned int> interconnect2;
	//load_obj(std::string(".//res//stall.obj"), vertices_pos2, texture_pos2, normals2, interconnect2);
	//Mesh *mesh2;
	//mesh2 = new Mesh(vertices_pos2, texture_pos2, normals2, interconnect2);
	
	//Entity *entity2 = new Entity(mesh2, &texture, glm::vec3(3, 0, -18));
	//entity2->setLightVars(1.0, 2.0);

	std::vector<float> vertices_pos_s;
	std::vector<float> texture_pos_s;
	std::vector<float> normals_s;
	std::vector<unsigned int> interconnect_s;

	load_obj(std::string(".//res//sphere.obj"), vertices_pos_s, texture_pos_s, normals_s, interconnect_s);

	Mesh *sphere = new Mesh(vertices_pos_s, texture_pos_s, normals_s, interconnect_s);
	Entity *sun = new Entity(sphere, &texture, glm::vec3(0, 10, -15));
	sun->setScale(glm::vec3(0.05, 0.05, 0.05));


	std::vector<float> vertices_pos_p;
	std::vector<float> texture_pos_p;
	std::vector<float> normals_p;
	std::vector<unsigned int> interconnect_p;

	load_obj(std::string(".//res//grassModel.obj"), vertices_pos_p, texture_pos_p, normals_p, interconnect_p);

	Mesh *mesh5 = new Mesh(vertices_pos_p, texture_pos_p, normals_p, interconnect_p);
	Texture *plants = new Texture(".//res//grassTexture.png", true);
	plants->setFakeLight(true);

	Texture *bkgTex = new Texture(".//res//grass.png", false);
	Texture *rTex = new Texture(".//res//mud.png", false);
	Texture *gTex = new Texture(".//res//grassFlowers.png", false);
	Texture *bTex = new Texture(".//res//path.png", false);
	Texture *bMap = new Texture(".//res//blendMap.png", false);

	TerrainTexture *backgroundTexture = new TerrainTexture(bkgTex->m_texture);
	TerrainTexture *rTexture = new TerrainTexture(rTex->m_texture);
	TerrainTexture *gTexture = new TerrainTexture(gTex->m_texture);
	TerrainTexture *bTexture = new TerrainTexture(bTex->m_texture);
	TerrainTexture *blendMap = new TerrainTexture(bMap->m_texture);

	TerrainTexturePack *texturePack = new TerrainTexturePack(backgroundTexture, rTexture, gTexture, bTexture);
	
	Terrain terrain(0, -1, texturePack, blendMap);
	float angle = 0.005f;
	//float angle = 90;
	Camera camera;
	//camera.position(glm::vec3());
	//Light light(glm::vec3(0, 2, -50), glm::vec3(1, 1, 1));


	Light light(glm::vec3(0, 30, -30), glm::vec3(1, 1, 1));
	//Light light(glm::vec3(4, 6, -30), glm::vec3(1, 1, 1));
	glm::vec4 skyColor(0.05f, 0.8f, 0.9f, 1.0f);

	MasterRenderer masterRenderer(&renderer, &camera, &light, skyColor);

	std::vector<Entity*> Entities;
	std::vector<Terrain*> Terrains;
	
	Terrains.push_back(&terrain);
	masterRenderer.listTerrains(Terrains);
	
	//Entities.push_back(entity4);
	Entities.push_back(entity);
	Entities.push_back(sun);
	Entities.push_back(new Entity(mesh4, &texture2, glm::vec3(0, 1, -4)));
	Entities.push_back(new Entity(mesh4, &texture2, glm::vec3(0, 1, -10)));
	Entities.push_back(new Entity(mesh4, &texture2, glm::vec3(0, 1, -20)));
	Entities.push_back(new Entity(mesh4, &texture2, glm::vec3(0, 3, -15)));
	//Entities.push_back(entity3);

	for (int i = 0; i < 500; i++)
	{
		Entities.push_back(new Entity(mesh5, plants, glm::vec3(1 + i * 1.5, 0, -1.0 * (rand() % 120))));
	}


	for (int i = 0; i < 350; i++)
	{
		Entities.push_back(new Entity(mesh4, &texture2, glm::vec3(2 + i * 2.0, 0, -1.0 * (rand() % 80))));
	}

	while (!display.IsClosed())
	{
		start_time = SDL_GetTicks();
		masterRenderer.clearFrame();
		camera.move();
		//light.position.x = light.position.x * cos(angle) - light.position.z * sin(angle);
		//light.position.z = light.position.x * sin(angle) + light.position.z * cos(angle);
		sun->setPosition(light.position);
		//light.move();
		masterRenderer.renderEntities(Entities);
		//shader.Bind();
		//shader.loadLight(light);
		//shader.loadViewMatrix(camera);
		//texture.Bind(0);
		//renderer.render(entity, shader);
		//shader.Stop();
		display.Update();

		end_time = SDL_GetTicks();
		if (end_time - start_time < frame_time)
		{
			SDL_Delay(frame_time - (end_time - start_time));
		}
		//entity->increasePosition(glm::vec3(0, 0, -1));
		//entity->increaseRotation(glm::vec3(0, 1, 0));
	}

	//delete mesh;
	for (Entity* e : Entities)
	{
		delete e;
	}

	return 0;
}
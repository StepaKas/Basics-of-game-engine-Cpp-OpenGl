#include "Object.h"

int Object::in_counter = 0;

void Object::init_models(Shader * shader)
{
	id = in_counter++;
	this->m_shader = shader;
	if (this->m_shader == nullptr) {
		cout << "Error" << endl;
	}
	for (size_t i = 0; i < modely.size(); i++)
	{
		

		modely[i]->init_VBO();
		modely[i]->init_VAO();

		modely[i]->shader = shader;
	}
}

void Object::run_in_the_loop()
{
	m_shader->use_shader();
	m_shader->spec_intensity(this->spec_intensity);
	// Poèítam støed tìlesa kolem, kterého budu dìlat rotaci
	float point_x_fin = 0;
	float point_y_fin = 0;
	float point_z_fin = 0;
	if (!(m_rot_x == 0 && m_rot_y == 0 && m_rot_z == 0)) {

	


		for (size_t i = 0; i < modely.size(); i++) {

			float point_x = 0;
			float point_y = 0;
			float point_z = 0;

			int x_offset = 0;
			int y_offset = 1;
			int z_offset = 2;
			int w_offset = 3;

		
			for (size_t j = 0; j < modely[i]->edges; j++)
			{			
				point_x += modely[i]->points[x_offset + i * modely[i]->edges * 2];
				point_y += modely[i]->points[y_offset + i * modely[i]->edges * 2];
				point_z += modely[i]->points[z_offset + i * modely[i]->edges * 2];
			}
			point_x_fin += point_x /  modely[i]->edges;
			point_y_fin += point_y /  modely[i]->edges;
			point_z_fin += point_z /  modely[i]->edges;
		}
		point_x_fin /= modely.size() ;
		point_y_fin /= modely.size() ;
		point_z_fin /= modely.size() ;
	}
	for (size_t i = 0; i < modely.size(); i++) {
		
		modely[i]->run_in_loop( point_x_fin, point_y_fin, point_z_fin);
	}
}

Object::Object()
{

}



#include "LightSource.h"


class TextureObject : public Object{
public:


	int texture_pos;

	TextureObject(int m_pos);


	void run_in_the_loop() {
		m_shader->use_shader();
		m_shader->send_texture_id((this)->texture_pos);
		m_shader->spec_intensity(this->spec_intensity);
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
				point_x_fin += point_x / modely[i]->edges;
				point_y_fin += point_y / modely[i]->edges;
				point_z_fin += point_z / modely[i]->edges;
			}
			point_x_fin /= modely.size();
			point_y_fin /= modely.size();
			point_z_fin /= modely.size();
		}
		for (size_t i = 0; i < modely.size(); i++) {
			if (texture_pos == TEXTURE_SKYBOX_ID) {
				glDepthMask(GL_FALSE);

				modely[i]->x = Camera::return_instance()->Position.x;
				modely[i]->y = Camera::return_instance()->Position.y;
				modely[i]->z = Camera::return_instance()->Position.z;
			}

			modely[i]->run_in_loop(point_x_fin, point_y_fin, point_z_fin, texture_pos);
			if (texture_pos == TEXTURE_SKYBOX_ID) {
				glDepthMask(GL_TRUE);

			}
		}
	}
};
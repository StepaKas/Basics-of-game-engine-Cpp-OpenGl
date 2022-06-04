#include "Model.h"

class Object  {
	
public:
	static int in_counter;
	int id;
	string name = "";
	float m_rot_x;
	float m_rot_y;
	float m_rot_z;

	float m_static_rot_x;
	float m_static_rot_y;
	float m_static_rot_z;

	float spec_intensity = 1.0;
	std::vector<Model*> modely;
	Shader* m_shader;
	void add_model(Model* _m) {

		modely.push_back(_m);
	}
	

	void add_model(Model* _m, float x, float y, float z, float rot_x, float rot_y, float rot_z, float scale_x = 1, float scale_y = 1, float scale_z = 1, float static_rot_x = 0, float static_rot_y = 0, float static_rot_z = 0) {
		
		//printf("%f %f %f\n", static_rot_x, static_rot_y, static_rot_z);
		m_static_rot_x = static_rot_x;
		m_static_rot_y = static_rot_y;
		m_static_rot_z = static_rot_z;

		m_rot_x = rot_x;
		m_rot_y = rot_y;
		m_rot_z = rot_z;

		_m->x = x;
		_m->y = y;
		_m->z = z;

		_m->rot_x = rot_x;
		_m->rot_y = rot_y;
		_m->rot_z = rot_z;

		_m->scale_x = scale_x;
		_m->scale_y = scale_y;
		_m->scale_z = scale_z;

		_m->static_rot_x = static_rot_x;
		_m->static_rot_y = static_rot_y;
		_m->static_rot_z = static_rot_z;

		modely.push_back(_m);
	}
	void init_models(Shader* shader);

	virtual void run_in_the_loop();
	Object();
};
	
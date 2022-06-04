const char * default_frag = "#version 330\n"
		"out vec4 frag_colour;"
		"in vec4 color;"
		"void main () {"
		"     frag_colour = color;"

	"}";

const char * default_vertex = "#version 330\n"
		"layout(location=0) in vec4 aPos;\n"
		"layout(location=1) in vec4 aColor;\n"

		"uniform mat4 model;\n"
		"uniform mat4 view;\n"
		"uniform mat4 proj;\n"
		"out vec4 color;\n"
		"uniform mat4 camMatrix;"	
		"void main () {\n"

		"     gl_Position = camMatrix * model * aPos  ;\n"
		"	  color = aColor;\n"
	"}";

const char* texture_frag = "#version 330\n"
"out vec4 frag_colour;"
"uniform sampler2D textureUnitID;"
"in vec2 uv;"

"in vec4 color;"
"void main () {"
//"     frag_colour = texture(textureUnitID, uv);"
"     frag_colour = texture(textureUnitID, uv);"

"}";

const char* texture_vertex = "#version 330\n"
"layout(location=0) in vec4 aPos;\n"
"layout(location=1) in vec4 aColor;\n"
"layout (location = 2) in vec2 aTex;"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 proj;\n"
"out vec4 color;\n"
"out vec2 uv;"
"uniform mat4 camMatrix;"
"void main () {\n"

"     gl_Position = camMatrix * model * aPos  ;\n"
"	  color = aColor;\n"
"	  uv = aTex;	"	
"}";


const char* lambert_vertex = "#version 400\n				"
"layout(location = 0)in vec3 position;				   "
"layout(location = 1)in vec3 normal;				   "
"out vec4 ex_worldPosition;							   "
"out vec4 ex_worldNormal;							   "

"uniform mat4 camMatrix;"			
"uniform mat4 model;"
"void main(void)									   "
"{													   "
"	gl_Position = camMatrix * model * vec4(position, 1.0);	   "
"	ex_worldPosition = model * vec4(position, 1.0);		   "
"	ex_worldNormal =  normalize ( transpose (inverse((model))) * vec4(normal, 1.0));			   "
"}";

const char* lambert_frag = "#version 400\n"
"in vec4 ex_worldPosition;			   "
"in vec4 ex_worldNormal;			   "
"out vec4 frag_colour;				   "

"struct light {"
"	vec3 position; "
"	vec4 diffuse;"
"	vec4  specular; "


"};"
"uniform light lights[3];"

"vec4 temp_sum =  vec4(0,0,0,0);"

"void main(void)					   "
"{									   "
"	for (int i = 0; i < 3; i++) {"
"	vec3 lightVec = lights[i].position - vec3(ex_worldPosition);"
"	float dist = length(lightVec);"
"	float a = 0.5;											 "
"	float b = 0.7;											 "
"	float inten = 1 / (a *dist  + 1.0);"
"	vec4 lightDirection = (vec4 (lights[i].position, 1)) - (ex_worldPosition);"	
"	float dot_product = max(dot(normalize(vec3(ex_worldNormal)), normalize(vec3(lightDirection)) ), 0.0);"

"	vec4 diffuse = dot_product * vec4(0.385 * lights[i].diffuse[0],0.647 *  lights[i].diffuse[1],0.812* lights[i].diffuse[2],1.0* lights[i].diffuse[3]);	   "
"	vec4 ambient = 0.1 / 3 *  (vec4(0.385, 0.647, 0.812, 1.0));						   "
"	temp_sum += 	 inten* diffuse +ambient;"	
"	}"
"	frag_colour =  temp_sum;    "
"}";


const char* phong_vertex = "#version 400\n				"
"layout(location = 0)in vec3 position;				   "
"layout(location = 1)in vec3 normal;				   "
"out vec4 ex_worldPosition;							   "
"out vec4 ex_worldNormal;							   "

"uniform mat4 camMatrix;"
"uniform mat4 model;"
"void main(void)									   "
"{													   "
"	gl_Position = camMatrix * model * vec4(position, 1.0);	   "
"	ex_worldPosition = model * vec4(position, 1.0);		   "
"	ex_worldNormal =  normalize ( transpose (inverse((model))) * vec4(normal, 1.0));	"
"}";

const char* phong_frag = "#version 400\n"
"in vec4 ex_worldPosition;			   "
"in vec4 ex_worldNormal;			   "
"out vec4 frag_colour;				   "
"uniform vec3 camPos;"




"struct light {"
"	vec3 position; "
"	vec4 diffuse;"	
"	vec4  specular; "


"};"
"uniform light lights[3];"
"vec4 temp_sum =  vec4(0,0,0,0);"

"void main(void)					   "
"{									   "

"	vec3 normal = normalize(vec3(ex_worldNormal));	"
"	vec3 viewDirection = normalize(camPos  -vec3 (ex_worldPosition));							  "
"	for (int i = 0; i < 3; i++) {"
	"	vec3 lightVec = lights[i].position - vec3(ex_worldPosition);"
	"	float dist = length(lightVec);"
	"	float a = 0.5;											 "
	"	float b = 0.7;											 "
	"	float inten = 1 / (a *dist  + 1.0);"



	"	vec3 lightDirection = normalize( lightVec);"
	"	float dot_product = max(dot((normal), (lightDirection)), 0.0);"

	"	vec4 diffuse = dot_product * vec4(0.385 * lights[i].diffuse[0],0.647 *  lights[i].diffuse[1],0.812* lights[i].diffuse[2],1.0* lights[i].diffuse[3]);	   "
	"	vec4 ambient = (0.1 / 3)* vec4(0.385, 0.647, 0.812, 1.0);						   "

	"	float specularLight = 0.5f;												  "

	"	vec3 reflectionDirection = (reflect((-lightDirection), (normal)));				  "
	"	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 10);"
	"	float specular = specAmount * specularLight;								  "
	"	temp_sum += diffuse * inten + ambient   + vec4(lights[i].specular[0],lights[i].specular[1],lights[i].specular[2],lights[i].specular[3]) * specular * inten;"	
"				}"
"	frag_colour = temp_sum ;  "
"}";


const char* blinn_vertex = "#version 400\n				"
"layout(location = 0)in vec3 position;				   "
"layout(location = 1)in vec3 normal;				   "
"out vec4 ex_worldPosition;							   "
"out vec4 ex_worldNormal;							   "

"uniform mat4 camMatrix;"
"uniform mat4 model;"
"void main(void)									   "
"{													   "
"	gl_Position = camMatrix * model * vec4(position, 1.0);	   "
"	ex_worldPosition = model * vec4(position, 1.0);		   "
"	ex_worldNormal =  normalize ( transpose (inverse((model))) * vec4(normal, 1.0));	"
"}";

const char* blinn_frag = "#version 400\n"
"in vec4 ex_worldPosition;			   "
"in vec4 ex_worldNormal;			   "
"out vec4 frag_colour;				   "
"uniform vec3 camPos;"
"struct light {"
"	vec3 position; "
"	vec4 diffuse;"
"	vec4  specular; "


"};"
"uniform light lights[3];"
"vec4 temp_sum =  vec4(0,0,0,0);"

"void main(void)					   "
"{									   "
"	vec3 normal = normalize(vec3(ex_worldNormal));	"
"	for (int i = 0; i < 3; i++) {"

"	vec3 lightVec = lights[i].position - vec3(ex_worldPosition);"

"	float dist = length(lightVec);"
"	float a = 0.5;											 "
"	float b = 0.7;											 "
"	float inten = 1 / (a *dist  + 1.0);"



"	vec3 lightDirection = normalize( lightVec);"
"	float dot_product = max(dot((normal), (lightDirection)), 0.0);"

"	vec4 diffuse = dot_product * vec4(0.385 * lights[i].diffuse[0],0.647 *  lights[i].diffuse[1],0.812* lights[i].diffuse[2],1.0* lights[i].diffuse[3]);	   "
"	vec4 ambient = (0.1 / 3)* vec4(0.385, 0.647, 0.812, 1.0);						   "

"	float specularLight = 0.5f;												  "
"	vec3 viewDirection = (camPos  -vec3 (ex_worldPosition));"
"	vec3 halfVector = normalize((lightVec +  viewDirection) / (dist +length(viewDirection)) );"		
"	float specAmount = pow(max(dot(halfVector, normal), 0.0f), 10);"
"	float specular = specAmount * specularLight;								  "
"	temp_sum += diffuse * inten + ambient   + vec4(lights[i].specular[0],lights[i].specular[1],lights[i].specular[2],lights[i].specular[3]) * specular * inten;"

"		}"
"	frag_colour = temp_sum ; "
"}";



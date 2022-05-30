/* Hello Triangle - código adaptado de https://learnopengl.com/#!Getting-started/Hello-Triangle 
 *
 * Código inicial para trabalhar com OpenGL 4
 * Adaptado pelos professores Vinicius Cassol e Rossana Queiroz
 * para uso didático em sala de aula
 * 
 */

#include <iostream>
#include <string>
#include <assert.h>

using namespace std;

//Dependêncais - "OpenGL Friends"
// GLAD
#include <glad/glad.h>	
// GLFW
#include <GLFW/glfw3.h>


// Protótipo da função de callback de teclado
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Protótipos das funções
int setupShader();
int setupGeometry();
int setupPacMan();
int setupPizza();
int setupSpiral();

// Dimensões da janela (pode ser alterado em tempo de execução)
const GLuint WIDTH = 1200, HEIGHT = 800;

// Código fonte do Vertex Shader (em GLSL): ainda hardcoded
const GLchar* vertexShaderSource = "#version 450\n"
"layout (location = 0) in vec3 position;\n"
"void main()\n"
"{\n"
//...pode ter mais linhas de código aqui!
"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}\0";

//Códifo fonte do Fragment Shader (em GLSL): ainda hardcoded
const GLchar* fragmentShaderSource = "#version 450\n"
"uniform vec4 inputColor;\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = inputColor;\n"
"}\n\0";

// Função MAIN
int main()
{
	// Inicialização da GLFW
	glfwInit();

	//Muita atenção aqui: alguns ambientes não aceitam essas configurações
	//Você deve adaptar para a versão do OpenGL suportada por sua placa
	//Sugestão: comente essas linhas de código para desobrir a versão e
	//depois atualize (por exemplo: 4.5 com 4 e 5)
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Essencial para computadores da Apple
//#ifdef __APPLE__
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif

	// Criação da janela GLFW
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Hello Triangulo! - Thiago Gomes | Willian de Sa", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Fazendo o registro da função de callback para a janela GLFW
	glfwSetKeyCallback(window, key_callback);

	// GLAD: carrega todos os ponteiros de funções da OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;

	}

	// Obtendo as informações de versão
	const GLubyte* renderer = glGetString(GL_RENDERER); /* get renderer string */
	const GLubyte* version = glGetString(GL_VERSION); /* version as a string */
	cout << "Renderer: " << renderer << endl;
	cout << "OpenGL version supported " << version << endl;

	// Definindo as dimensões da viewport com as mesmas dimensões da janela da aplicação
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);


	// Compilando e buildando o programa de shader
	GLuint shaderID = setupShader();

	// Gerando um buffer simples, com a geometria de um triângulo
	GLuint VAO = setupGeometry();
	

	// Enviando a cor desejada (vec4) para o fragment shader
	// Utilizamos a variáveis do tipo uniform em GLSL para armazenar esse tipo de info
	// que não está nos buffers
	GLint colorLoc = glGetUniformLocation(shaderID, "inputColor");
	assert(colorLoc > -2);
	
	glUseProgram(shaderID);
	

	// Loop da aplicação - "game loop"
	while (!glfwWindowShouldClose(window))
	{
		// Checa se houveram eventos de input (key pressed, mouse moved etc.) e chama as funções de callback correspondentes
		glfwPollEvents();

		// Limpa o buffer de cor
		glClearColor(0.8f, 0.8f, 0.8f, 1.0f); //cor de fundo
		glClear(GL_COLOR_BUFFER_BIT);

		glLineWidth(10);
		glPointSize(20);

		// Chamada de desenho - drawcall
		// Poligono Preenchido - GL_TRIANGLES
		// Contornos - GL_LINE_LOOP
		// Pontos - GL_POINTS

		// Ex. 5 Item A
		// glUniform4f(colorLoc, 0.0f, 0.0f, 1.0f, 1.0f); //enviando cor para variável uniform inputColor
		// glBindVertexArray(VAO);
		// glDrawArrays(GL_TRIANGLES, 0, 3);
		// glDrawArrays(GL_TRIANGLES, 4, 6);

		// Ex. 5 Item B
		// glUniform4f(colorLoc, 0.0f, 0.0f, 1.0f, 1.0f);
		// glBindVertexArray(VAO);
		// glDrawArrays(GL_LINE_LOOP, 0, 3);
		// glDrawArrays(GL_LINE_LOOP, 4, 6);

		// Ex. 5 Item C
		// glUniform4f(colorLoc, 0.0f, 0.0f, 1.0f, 1.0f);
		// glBindVertexArray(VAO);
		// glDrawArrays(GL_POINTS, 0, 3);
		// glDrawArrays(GL_POINTS, 4, 6);

		// Ex. 5 Item D
		// glUniform4f(colorLoc, 0.0f, 0.0f, 1.0f, 1.0f); //enviando cor para variável uniform inputColor
		// glBindVertexArray(VAO);
		// glDrawArrays(GL_TRIANGLES, 0, 3);
		// glDrawArrays(GL_TRIANGLES, 4, 6);
		// glUniform4f(colorLoc, 0.0f, 1.0f, 0.0f, 1.0f);
		// glBindVertexArray(VAO);
		// glDrawArrays(GL_LINE_LOOP, 0, 3);
		// glDrawArrays(GL_LINE_LOOP, 4, 6);
		// glUniform4f(colorLoc, 1.0f, 0.0f, 0.0f, 1.0f);
		// glBindVertexArray(VAO);
		// glDrawArrays(GL_POINTS, 0, 3);
		// glDrawArrays(GL_POINTS, 4, 6);

		// Ex. 6 Item A
		// glUniform4f(colorLoc, 0.0f, 0.0f, 1.0f, 1.0f); //enviando cor para variável uniform inputColor
		// glBindVertexArray(VAO);
		// glDrawArrays(GL_LINE_LOOP, 0, 8);

		// Ex. 6 Item B
		// glUniform4f(colorLoc, 0.0f, 0.0f, 1.0f, 1.0f); //enviando cor para variável uniform inputColor
		// glBindVertexArray(VAO);
		// glDrawArrays(GL_LINE_LOOP, 0, 5);

		// Ex. 6 Item C
		// VAO = setupPacMan();
		// glUniform4f(colorLoc, 0.0f, 0.0f, 1.0f, 1.0f); //enviando cor para variável uniform inputColor
		// glBindVertexArray(VAO);
		// glDrawArrays(GL_LINE_LOOP, 0, 86);

		// Ex. 6 Item D
		// VAO = setupPizza();
		// glUniform4f(colorLoc, 1.0f, 0.0f, 0.0f, 1.0f); //enviando cor para variável uniform inputColor
		// glBindVertexArray(VAO);
		// glDrawArrays(GL_LINE_LOOP, 0, 21);

		// Ex. 6 Item E
		// glUniform4f(colorLoc, 0.0f, 0.0f, 1.0f, 1.0f); //enviando cor para variável uniform inputColor
		// glBindVertexArray(VAO);
		// glDrawArrays(GL_LINE_LOOP, 0, 10);

		// Ex. 7
		// VAO = setupSpiral();
		// glUniform4f(colorLoc, 0.0f, 0.75f, 0.0f, 1.0f); //enviando cor para variável uniform inputColor
		// glBindVertexArray(VAO);
		// glDrawArrays(GL_LINE_STRIP, 0, 122);

		// Ex. 8 Item C
		// glUniform4f(colorLoc, 0.0f, 0.0f, 1.0f, 1.0f); //enviando cor para variável uniform inputColor
		// glBindVertexArray(VAO);
		// glDrawArrays(GL_LINE_LOOP, 0, 3);
		// glUniform4f(colorLoc, 1.0f, 0.0f, 0.0f, 1.0f);
		// glBindVertexArray(VAO);
		// glDrawArrays(GL_POINTS, 0, 1);;
		// glUniform4f(colorLoc, 0.0f, 1.0f, 0.0f, 1.0f);
		// glBindVertexArray(VAO);
		// glDrawArrays(GL_POINTS, 1, 1);
		// glUniform4f(colorLoc, 0.0f, 0.0f, 0.75f, 1.0f);
		// glBindVertexArray(VAO);
		// glDrawArrays(GL_POINTS, 2, 1);

		// Ex. 9
		glUniform4f(colorLoc, 0.0f, 0.0f, 1.0f, 1.0f); //enviando cor para variável uniform inputColor
		glBindVertexArray(VAO);
		glDrawArrays(GL_LINE_LOOP, 0, 4);
		glUniform4f(colorLoc, 0.0f, 0.75f, 0.0f, 1.0f); //enviando cor para variável uniform inputColor
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 4, 3);
		glUniform4f(colorLoc, 1.0f, 0.0f, 0.0f, 0.0f); //enviando cor para variável uniform inputColor
		glBindVertexArray(VAO);
		glDrawArrays(GL_LINE_LOOP, 7, 4);
		glUniform4f(colorLoc, 1.0f, 0.0f, 0.0f, 0.0f); //enviando cor para variável uniform inputColor
		glBindVertexArray(VAO);
		glDrawArrays(GL_LINE_LOOP, 11, 4);
				
		glBindVertexArray(0);

		// Troca os buffers da tela
		glfwSwapBuffers(window);
	}
	// Pede pra OpenGL desalocar os buffers
	glDeleteVertexArrays(1, &VAO);
	// Finaliza a execução da GLFW, limpando os recursos alocados por ela
	glfwTerminate();
	return 0;
}

// Função de callback de teclado - só pode ter uma instância (deve ser estática se
// estiver dentro de uma classe) - É chamada sempre que uma tecla for pressionada
// ou solta via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

//Esta função está basntante hardcoded - objetivo é compilar e "buildar" um programa de
// shader simples e único neste exemplo de código
// O código fonte do vertex e fragment shader está nos arrays vertexShaderSource e
// fragmentShader source no iniçio deste arquivo
// A função retorna o identificador do programa de shader
int setupShader()
{
	// Vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// Checando erros de compilação (exibição via log no terminal)
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// Checando erros de compilação (exibição via log no terminal)
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Linkando os shaders e criando o identificador do programa de shader
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// Checando por erros de linkagem
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

// Esta função está bastante harcoded - objetivo é criar os buffers que armazenam a 
// geometria de um triângulo
// Apenas atributo coordenada nos vértices
// 1 VBO com as coordenadas, VAO com apenas 1 ponteiro para atributo
// A função retorna o identificador do VAO
int setupGeometry()
{
	// Aqui setamos as coordenadas x, y e z do triângulo e as armazenamos de forma
	// sequencial, já visando mandar para o VBO (Vertex Buffer Objects)
	// Cada atributo do vértice (coordenada, cores, coordenadas de textura, normal, etc)
	// Pode ser arazenado em um VBO único ou em VBOs separados

	// Ex. 5
	/*
	GLfloat vertices[] = {
		0.3, -0.5, 0.0,
		- 0.1, -0.5, 0.0,
		 0.1, 0.1, 0.0,
		
		-0.2, -0.5, 0.0,
		-0.45, -0.0, 0.0,
		-0.2, 0.5, 0.0,
	};
	*/

	// Ex. 6 Item A
	/*
	GLfloat vertices[] = {
		-0.5, 0.95, 0.0,
		-0.75, 0.5, 0.0,
		-0.75, -0.5, 0.0,
		-0.5, -0.85, 0.0,
		
		0.25, -0.85, 0.0,
		0.45, -0.5, 0.0,
		0.45, 0.5, 0.0,
		0.25, 0.95, 0.0
	};
	*/

	// Ex. 6 Item B
	/*
	GLfloat vertices[] = {
		0.0, 0.95, 0.0,

		-0.75, 0.40, 0.0,
		-0.5, -0.75, 0.0,
		
		0.5, -0.75, 0.0,
		0.75, 0.40, 0.0		
	};
	*/

	// Ex. 6 Item E
	/*
	GLfloat vertices[] = {
		0.0, 0.95, 0.0,

		-0.25, 0.50, 0.0,
		-0.75, 0.50, 0.0,
		-0.25, 0.0, 0.0,

		-0.75, -0.75, 0.0,
		0.0, -0.25, 0.0,
		0.75, -0.75, 0.0,

		0.25, 0.0, 0.0,
		0.75, 0.50, 0.0,
		0.25, 0.50, 0.0,
	};
	*/

	// Ex. 8 Item C
	/*
	GLfloat vertices[] = {
		0.0, 0.6, 0.0,
		-0.6, -0.5, 0.0,
		0.6, -0.3, 0.0,
	};
	*/

	// Ex. 9
	GLfloat vertices[] = {
		-0.3, 0.5, 0.0,
		-0.3, 0.0, 0.0,
		0.3, 0.0, 0.0,
		0.3, 0.5, 0.0,


		0.0, 0.8, 0.0,
		-0.35, 0.5, 0.0,
		0.35, 0.5, 0.0,

		-0.05, 0.0, 0.0,
		-0.05, 0.20, 0.0,
		0.05, 0.20, 0.0,
		0.05, 0.0, 0.0,

		-0.25, 0.3, 0.0,
		-0.25, 0.4, 0.0,
		-0.15, 0.4, 0.0,
		-0.15, 0.3, 0.0
	};

	GLuint VBO, VAO;

	//Geração do identificador do VBO
	glGenBuffers(1, &VBO);
	//Faz a conexão (vincula) do buffer como um buffer de array
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Envia os dados do array de floats para o buffer da OpenGl
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	 //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

	//Geração do identificador do VAO (Vertex Array Object)
	glGenVertexArrays(1, &VAO);
	// Vincula (bind) o VAO primeiro, e em seguida  conecta e seta o(s) buffer(s) de vértices
	// e os ponteiros para os atributos 
	glBindVertexArray(VAO);
	//Para cada atributo do vertice, criamos um "AttribPointer" (ponteiro para o atributo), indicando: 
	// Localização no shader * (a localização dos atributos devem ser correspondentes no layout especificado no vertex shader)
	// Numero de valores que o atributo tem (por ex, 3 coordenadas xyz) 
	// Tipo do dado
	// Se está normalizado (entre zero e um)
	// Tamanho em bytes 
	// Deslocamento a partir do byte zero 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Observe que isso é permitido, a chamada para glVertexAttribPointer registrou o VBO como o objeto de buffer de vértice 
	// atualmente vinculado - para que depois possamos desvincular com segurança
	glBindBuffer(GL_ARRAY_BUFFER, 0); 

	// Desvincula o VAO (é uma boa prática desvincular qualquer buffer ou array para evitar bugs medonhos)
	glBindVertexArray(0); 

	return VAO;
}

int setupPacMan()
{
	// Vertices (85 vertices * 3 coordinates) + (1 origin vertex * 3 coordinates)
	GLfloat vertices[258];

	// Radius
	GLdouble radius = 0.5;

	// Origin
	GLdouble originX = 0.0;
	GLdouble originY = 0.0;

	// PI
	GLfloat PI = 3.141592;

	int v = 0;

	for (int i = 0; i < 85; i++) {
		// Fill 85% of the circle

		// Modified Angle
		double angulo = 2 * PI * i / 100;

		// Coordinates
		double xVertice = cos(angulo) * radius;
		double yVertice = sin(angulo) * radius;

		// Vertex
		vertices[v++] = originX + xVertice;
		vertices[v++] = originY + yVertice;
		vertices[v++] = 0.0;
	}

	// Origin
	vertices[v++] = 0.0;
	vertices[v++] = 0.0;
	vertices[v++] = 0.0;

	GLuint VBO, VAO;

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return VAO;
}

int setupPizza()
{
	// Vertices (20 vertices * 3 coordinates) + (1 origin vertex * 3 coordinates)
	GLfloat vertices[63];

	// Radius
	GLdouble radius = 0.5;

	// Origin
	GLdouble originX = 0.0;
	GLdouble originY = 0.0;

	// PI
	GLfloat PI = 3.141592;

	int v = 0;

	for (int i = 0; i < 20; i++) {
		// Fill 20% of the circle

		// Modified Angle
		double angulo = 2 * PI * i / 100;

		// Coordinates
		double xVertice = cos(angulo) * radius;
		double yVertice = sin(angulo) * radius;

		// Vertex
		vertices[v++] = originX + xVertice;
		vertices[v++] = originY + yVertice;
		vertices[v++] = 0.0;
	}

	// Origin
	vertices[v++] = 0.0;
	vertices[v++] = 0.0;
	vertices[v++] = 0.0;

	GLuint VBO, VAO;

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return VAO;
}

int setupSpiral()
{
	GLfloat PI = 3.141592;

	GLfloat vertices[366];

	GLdouble radius = 0.01;
	GLfloat angle = 0;

	GLfloat originX = 0;
	GLfloat originY = 0;

	GLfloat radiusDist = 0.05;

	int v = 0;

	vertices[v++] = 0.0;
	vertices[v++] = 0.0;
	vertices[v++] = 0.0;

	for (int i = 0; i < 121; i++)
	{
		vertices[v++] = GLfloat(originX + radiusDist * cos(angle));
		vertices[v++] = GLfloat(originY + radiusDist * sin(angle));
		vertices[v++] = GLfloat(0.0);

		radiusDist += 0.004;
		angle += 0.200;
	}

	GLuint VBO, VAO;

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return VAO;
}
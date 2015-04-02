#include "Mesh.h"

struct Face
{
	int vertex; //! vertex ID for the face
	int iUV; //! UV ID for the face
	int norm; //! normal ID for the face
};
struct VertexIndex
{
	int uvID;
	int normalID;
};

Mesh::Mesh(std::string filename, GLuint _shaderHandle)
{
	myShaderHandle = _shaderHandle;
	m_FileName = filename;
	init();
	std::cout << "C| Mesh Created!\n";
}
Mesh::~Mesh()
{

}
void Mesh::init()
{
	//model loader stuff goes here and then inputted into the
	//points, colours and indices stuff as well as anything extra
	//that I add like texture coords and stuff
	m_FileName = "resources/" + m_FileName;
	load(m_FileName);
	genMesh();
}
void Mesh::genMesh()
{
	glGenBuffers(4, VBOHandle);
	positionBufferHandle = VBOHandle[0];
	normalBufferHandle = VBOHandle[1];
	uvBufferHandle = VBOHandle[2];
	index_buffer = VBOHandle[3];

	glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, (points.size() * 3) * sizeof(float), &points[0].x, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, normalBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, (normals.size() * 3) * sizeof(float), &points[0].x, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, uvBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, (uvData.size() * 2) * sizeof(float), &uvData[0].x, GL_STATIC_DRAW);

	// Create and set-up the vertex array object
	glGenVertexArrays( 1, &VAOHandle );
	glBindVertexArray(VAOHandle);

	GLint vertPos;
	GLint vertNormal;
	GLint texCoords;

	vertPos = glGetAttribLocation(myShaderHandle,"i_VertPosition");
	glEnableVertexAttribArray(vertPos);
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
	glVertexAttribPointer( vertPos, 3, GL_FLOAT, FALSE, 0, (GLubyte *)NULL );

	vertNormal = glGetAttribLocation(myShaderHandle,"i_VertNormal");
	glEnableVertexAttribArray(vertNormal);
	glBindBuffer(GL_ARRAY_BUFFER, normalBufferHandle);
	glVertexAttribPointer( vertNormal, 3, GL_FLOAT, FALSE, 0, (GLubyte *)NULL );
	
	texCoords = glGetAttribLocation(myShaderHandle, "i_TexCoords");
	glEnableVertexAttribArray(texCoords);
	glBindBuffer(GL_ARRAY_BUFFER, uvBufferHandle);
	glVertexAttribPointer(texCoords, 2, GL_FLOAT, FALSE, 0, (GLubyte *)NULL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()  * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

}
void Mesh::genTexture(std::string _texName)
{
	myTexture = 0;
	if(myImage.loadFromFile(_texName))
	{
		glGenTextures(1, &myTexture);
		glBindTexture(GL_TEXTURE_2D, myTexture);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, myImage.getSize().x, myImage.getSize().y, GL_RGBA, GL_UNSIGNED_BYTE, myImage.getPixelsPtr());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	}
	hasTexture=true;
}
void Mesh::load(std::string _fileName)
{
	std::vector<Face> myFaces;
	std::vector<sf::Vector2f> _textureUVsOrderd; //! UVs after ordering in accordance to faces
	std::vector<sf::Vector3f> _normalsOrderd; //! Normals sorted for rendering
	std::vector<sf::Vector3f> _verticesOrderd; //! Verts for mesh
	std::vector<sf::Vector2f> _textureUVs; //! UVs for texture
	std::vector<sf::Vector3f> _vertices; //! Verts for mesh
	std::vector<sf::Vector3i> _faces;
	std::vector<sf::Vector3f> _normals;
	myFaces.clear();
	_vertices.clear();
	_textureUVs.clear();
	_textureUVsOrderd.clear();
	_normalsOrderd.clear();
	_normals.clear();
	std::vector<VertexIndex> vertexIndexes;
	vertexIndexes.clear();
	std::ifstream objectFile(_fileName.c_str());	//! stream the obj file
	if(!objectFile) //! if fail return
	{
		return;
	}
	std::string tmp(std::istreambuf_iterator<char>(objectFile), (std::istreambuf_iterator<char>()));
	std::istringstream buffer(tmp);
	objectFile.close();

	float min[3]=
	{
		500,	//! x min
		500,	//! y min
		500,	//! z min
	},
	max[3]=
		{
			-500,	//! x max
			-500,	//! y max
			-500,	//! z max
		};
		std::string line;
		while(std::getline(buffer, line)) 
		{
			line.erase(line.find_last_not_of(" \n\r\t")+1);
			if(line.find_first_of("#") != -1)
			{
				continue; //! skip the comments in the obj files
			}
			std::string prefix = line.substr(0, line.find_first_of(" "));
			if(prefix.compare("vt")==0) //!if there is a texture coord
			{
				line = line.substr(line.find_first_of("vt")+2);
				sf::Vector2f uv;
				uv.x = 0;
				uv.y = 0;
				std::istringstream s(line);
				s>>uv.x;
				s>>uv.y;
				uv.y *=-1;
				_textureUVs.push_back(uv);
			}
			if(prefix.compare("v")==0) //! if there is a vertex
			{
				line = line.substr(line.find_first_of("v")+2);
				sf::Vector3f vert;
				std::istringstream s(line);
				s>>vert.x;
				s>>vert.y;
				s>>vert.z;
				if(vert.x<min[0])
					min[0] = vert.x;
				if(vert.y<min[1])
					min[1] = vert.y;
				if(vert.z<min[2])
					min[2] = vert.z;
				if(vert.x>max[0])
					max[0] = vert.x;
				if(vert.y>max[1])
					max[1] = vert.y;
				if(vert.z>max[2])
					max[2] = vert.z;
				_vertices.push_back(vert);
			}
			if(prefix.compare("vn")==0) //! if there is a normal
			{
				line = line.substr(line.find_first_of("vn")+2);
				sf::Vector3f normal;
				std::istringstream s(line);
				s>>normal.x;
				s>>normal.y;
				s>>normal.z;
				_normals.push_back(normal);
			}
			if(prefix.compare("f")==0)
			{
				line = line.substr(line.find_first_of("f")+2);
				Face newFace;
				std::string curVertex = "";
				std::string curUV = "";
				std::string curNorm = "";
				unsigned int step = 0;
				for(auto iter : line)
				{
					if(iter == '/')
					{
						step ++;
						continue;
					}
					else if(iter == ' ')
					{
						if(step == 2)
						{
							newFace.vertex = atoi(curVertex.c_str());
							newFace.iUV = atoi(curUV.c_str());
							newFace.norm = atoi(curNorm.c_str());
							myFaces.push_back(newFace);
							step = 0;
							curVertex = "";
							curUV = "";
							curNorm = "";
							//End
						}
						continue;
					}
					else if(step == 0) //! vertex
					{
						curVertex += iter;
					}
					else if(step == 1) //! UV ID
					{
						curUV += iter;
					}
					else if(step == 2) //! normal ID
					{
						curNorm += iter;
					}
				}
				newFace.vertex = atoi(curVertex.c_str());
				newFace.iUV = atoi(curUV.c_str());
				newFace.norm = atoi(curNorm.c_str());
				myFaces.push_back(newFace);
				step = 0;
				curVertex = "";
				curUV = "";
				curNorm = "";
				sf::Vector3i face;
				face.x = 0;
				face.y = 0;
				face.z = 0;
				int index = line.find_first_of(" ");
				int start = 0;
				std::string face_data;
				std::string l2="";
				int space_index = line.find_first_of(" ", start+1);
				l2 = line.substr(start, space_index-start);
				while(space_index!= -1) {
					l2 = line.substr(start, space_index-start);
					//! new face
					face_data.append(l2.substr(0, l2.find("/")));
					face_data.append(" ");
					start += space_index;
					space_index = line.find_first_of(" ", start+1);
				}
				l2 = line.substr(line.find_last_of(" "));
				face_data.append(l2.substr(0, l2.find("/")));
				std::istringstream s(face_data);
				s >> face.x;
				s >> face.y;
				s >> face.z;
				face.x-=1;
				face.y-=1;
				face.z-=1;
				_faces.push_back(face);
			}
		}
		vertexIndexes.resize(_vertices.size());

		////now do centering
		//for(size_t i=0;i<_vertices.size();i++) {
		//	_vertices[i].x -= min[0];
		//	_vertices[i].y -= min[1];
		//	_vertices[i].z -= min[2];
		//	_vertices[i].x = (_vertices[i].x/(max[0]-min[0])) -0.5f;
		//	_vertices[i].y = (_vertices[i].y/(max[1]-min[1])) -0.5f;
		//	_vertices[i].z = (_vertices[i].z/(max[2]-min[2])) -0.5f;
		//}

		_faces.clear();
		int i = 0;
		int step = 0;
		for(auto iter : myFaces)
		{
			_verticesOrderd.push_back(_vertices.at(iter.vertex-1));
			_textureUVsOrderd.push_back(_textureUVs.at(iter.iUV - 1));
			_normalsOrderd.push_back(_normals.at(iter.norm-1));
			step ++;
			if(step == 3)
			{
				_faces.push_back(sf::Vector3i(i,i+1,i+2));
				i+=3;
				step = 0;
			}
		}

		//! assigns the vectors to the mesh
		points = _verticesOrderd;
		for(size_t i = 0; i < _faces.size(); ++i)
		{
			indices.push_back(_faces[i].x);
			indices.push_back(_faces[i].y);
			indices.push_back(_faces[i].z);
		}
		uvData = _textureUVsOrderd;
		normals = _normalsOrderd;

		_vertices.clear();
		_textureUVs.clear();
		_normals.clear();
		_faces.clear();

		return;
}
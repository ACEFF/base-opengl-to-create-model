#define _CRT_SECURE_NO_WARNINGS
#include "objmodel.h"
#include"Utils.h"
#include <string>
#include <sstream>
#include <vector>


void ObjModel::Init(const char* ObjModel)
{
	struct FloatData
	{
		float v[3];
	};

	struct VerticeDefine
	{
		int posIndex;
		int texcoordIndex;
		int normalIndex;
	};

	std::vector<FloatData> positions, texcoords, normals;
	std::vector<VerticeDefine> vertexes;
	std::vector<int> indexes;

	unsigned char* filecontent = LoadFileContent(ObjModel);
	std::stringstream ssFileContent((char*)filecontent);
	std::string temp;
	char szOneLine[256];
	while (!ssFileContent.eof())
	{
		memset(szOneLine, 0, 256);
		ssFileContent.getline(szOneLine, 256);
		if (strlen(szOneLine) > 0)
		{
			if (szOneLine[0] == 'v')
			{
				std::stringstream ssOneLine(szOneLine);

				if (szOneLine[1] == 't')
				{
					//纹理坐标
					ssOneLine >> temp;
					FloatData floatData;
					ssOneLine >> floatData.v[0];
					ssOneLine >> floatData.v[1];
					texcoords.push_back(floatData);
				}
				else if (szOneLine[1] == 'n')
				{
					//法线
					ssOneLine >> temp;
					FloatData floatData;
					ssOneLine >> floatData.v[0];
					ssOneLine >> floatData.v[1];
					ssOneLine >> floatData.v[2];
					normals.push_back(floatData);
				}
				else
				{
					//坐标点
					ssOneLine >> temp;
					FloatData floatData;
					ssOneLine >> floatData.v[0];
					ssOneLine >> floatData.v[1];
					ssOneLine >> floatData.v[2];
					positions.push_back(floatData);
				}
			}
			else if (szOneLine[0] == 'f')
			{
				std::stringstream ssOneLine(szOneLine);
				ssOneLine >> temp;
				std::string vertexStr;
				for (int i = 0; i < 3; i++)
				{
					ssOneLine >> vertexStr;
					size_t pos = vertexStr.find_first_of('/');
					std::string posIndexStr = vertexStr.substr(0, pos);
					size_t pos2 = vertexStr.find_first_of('/', pos + 1);
					std::string texcoordIndeStr = vertexStr.substr(pos + 1, pos2 - 1 - pos);
					std::string normalIndexStr = vertexStr.substr(pos2 + 1, vertexStr.length() - 1 - pos2);
					VerticeDefine vd;
					vd.posIndex = atoi(posIndexStr.c_str());
					vd.texcoordIndex = atoi(texcoordIndeStr.c_str());
					vd.normalIndex = atoi(normalIndexStr.c_str());
					//去重
					int nCurrentVertexIndex = -1;
					int nCurrentVertexCount = (int)vertexes.size();
					for (int j = 0; j < nCurrentVertexCount; ++j)
					{
						if (vertexes[j].posIndex == vd.posIndex && vertexes[j].normalIndex == vd.normalIndex && vertexes[j].texcoordIndex == vd.texcoordIndex)
						{
							nCurrentVertexIndex = j;
							break;
						}
					}
					if (nCurrentVertexIndex == -1)
					{
						nCurrentVertexIndex = (int)vertexes.size();
						vertexes.push_back(vd);
					}
					indexes.push_back(nCurrentVertexIndex);
				}
			}
		}
	}

	mIndexCount = (int)indexes.size();
	mIndices = new int[mIndexCount];

	for (int i = 0; i < mIndexCount; ++i)
	{
		mIndices[i] = indexes[i];
	}

	int vertexCount = (int)vertexes.size();
	mVertexes = new VertexData[vertexCount];

	for (int i = 0; i < vertexCount; ++i)
	{
		memcpy(mVertexes[i].position, positions[vertexes[i].posIndex - 1].v, sizeof(float) * 3);
		memcpy(mVertexes[i].texcoord, texcoords[vertexes[i].texcoordIndex - 1].v, sizeof(float) * 2);
		memcpy(mVertexes[i].normal, normals[vertexes[i].normalIndex - 1].v, sizeof(float) * 3);
	}
	delete filecontent;
}

void ObjModel::Draw()
{
	//关闭背面渲染，提高效率
	glEnable(GL_CULL_FACE);

	//glPolygonMode(GL_FRONT, GL_LINE);
	/*glPopMatrix();*/
	glTranslatef(0.0f, 0.0f, -3.0f);
	glRotatef(30.0f, 0.0f, 1.0f, 0.0f);
	glBegin(GL_TRIANGLES);

	for (int i = 0; i < mIndexCount; ++i)
	{
		glTexCoord2fv(mVertexes[mIndices[i]].texcoord);
		glNormal3fv(mVertexes[mIndices[i]].normal);
		glVertex3fv(mVertexes[mIndices[i]].position);
	}
	glEnd();
	/*glPopMatrix();*/
}
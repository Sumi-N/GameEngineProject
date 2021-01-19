#include "FBXImporter.h"
#include <inttypes.h>

bool FBXImporter::Import(const char* filepath)
{
	FILE* fp = fopen(filepath, "rb");

	if (!fp) return false;

	fseek(fp, 0, SEEK_END);
	long file_size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	auto* content = new ofbx::u8[file_size];
	fread(content, 1, file_size, fp);
	g_scene = ofbx::load((ofbx::u8*)content, file_size, (ofbx::u64)ofbx::LoadFlags::TRIANGULATE);
	if (!g_scene)
	{
		DEBUG_PRINT(ofbx::getError());
	}
	else
	{
		saveAsOBJ(*g_scene, "out.obj");
	}

	//int count = g_scene->getMesh(0)->getGeometry()->getVertexCount();
	//
	//const ofbx::Pose* pose;
	//const ofbx::Mesh* mesh;
	//mesh = g_scene->getMesh(0);
	//pose = mesh->getPose();

	delete[] content;

	fclose(fp);
}

bool FBXImporter::saveAsOBJ(ofbx::IScene& scene, const char* path)
{
	FILE* fp = fopen(path, "wb");
	if (!fp) return false;
	int obj_idx = 0;
	int indices_offset = 0;
	int normals_offset = 0;
	int mesh_count = scene.getMeshCount();
	for (int i = 0; i < mesh_count; ++i)
	{
		fprintf(fp, "o obj%d\ng grp%d\n", i, obj_idx);

		const ofbx::Mesh& mesh = *scene.getMesh(i);
		const ofbx::Geometry& geom = *mesh.getGeometry();
		int vertex_count = geom.getVertexCount();
		const ofbx::Vec3* vertices = geom.getVertices();
		for (int i = 0; i < vertex_count; ++i)
		{
			ofbx::Vec3 v = vertices[i];
			fprintf(fp, "v %f %f %f\n", v.x, v.y, v.z);
		}

		bool has_normals = geom.getNormals() != nullptr;
		if (has_normals)
		{
			const ofbx::Vec3* normals = geom.getNormals();
			int count = geom.getIndexCount();

			for (int i = 0; i < count; ++i)
			{
				ofbx::Vec3 n = normals[i];
				fprintf(fp, "vn %f %f %f\n", n.x, n.y, n.z);
			}
		}

		bool has_uvs = geom.getUVs() != nullptr;
		if (has_uvs)
		{
			const ofbx::Vec2* uvs = geom.getUVs();
			int count = geom.getIndexCount();

			for (int i = 0; i < count; ++i)
			{
				ofbx::Vec2 uv = uvs[i];
				fprintf(fp, "vt %f %f\n", uv.x, uv.y);
			}
		}

		const int* faceIndices = geom.getFaceIndices();
		int index_count = geom.getIndexCount();
		bool new_face = true;
		for (int i = 0; i < index_count; ++i)
		{
			if (new_face)
			{
				fputs("f ", fp);
				new_face = false;
			}
			int idx = (faceIndices[i] < 0) ? -faceIndices[i] : (faceIndices[i] + 1);
			int vertex_idx = indices_offset + idx;
			fprintf(fp, "%d", vertex_idx);

			if (has_uvs)
			{
				int uv_idx = normals_offset + i + 1;
				fprintf(fp, "/%d", uv_idx);
			}
			else
			{
				fprintf(fp, "/");
			}

			if (has_normals)
			{
				int normal_idx = normals_offset + i + 1;
				fprintf(fp, "/%d", normal_idx);
			}
			else
			{
				fprintf(fp, "/");
			}

			new_face = faceIndices[i] < 0;
			fputc(new_face ? '\n' : ' ', fp);
		}

		indices_offset += vertex_count;
		normals_offset += index_count;
		++obj_idx;
	}
	fclose(fp);
	return true;
}

template <int N>
void catProperty(char(&out)[N], const ofbx::IElementProperty& prop)
{
	char tmp[128];
	switch (prop.getType())
	{
	case ofbx::IElementProperty::DOUBLE: sprintf_s(tmp, "%f", prop.getValue().toDouble()); break;
	case ofbx::IElementProperty::LONG: sprintf_s(tmp, "%" PRId64, prop.getValue().toU64()); break;
	case ofbx::IElementProperty::INTEGER: sprintf_s(tmp, "%d", prop.getValue().toInt()); break;
	case ofbx::IElementProperty::STRING: prop.getValue().toString(tmp); break;
	default: sprintf_s(tmp, "Type: %c", (char)prop.getType()); break;
	}
	strcat_s(out, tmp);
}

bool FBXImporter::LoadData()
{
	const ofbx::IElement* root = g_scene->getRootElement();

	if (root && root->getFirstChild())
	{
		for (const ofbx::IElement* element = root->getFirstChild(); element; element = element->getSibling())
		{
			auto id = element->getID();
			char label[128];
			id.toString(label);
			strcat_s(label, "(");
			ofbx::IElementProperty* prop = element->getFirstProperty();
			bool first = true;
			while (prop)
			{
				if (!first)
					strcat_s(label, ", ");
				first = false;
				catProperty(label, *prop);
				prop = prop->getNext();
			}
			strcat_s(label, ")");
		}
	}

	return true;
}
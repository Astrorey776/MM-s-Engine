#include "Globals.h"
#include "Application.h"
#include "ModuleResources.h"

ModuleResources::ModuleResources(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	//Init physfs
	PHYSFS_init(nullptr);
	PHYSFS_mount(".", nullptr, 1);
	SetNewPath("Assets");

}

ModuleResources::~ModuleResources()
{



}



update_status ModuleResources::Update(float dt)
{
	ImMainMenuBar::ThemeStyleW();
	ImMainMenuBar::ThemeStyleChanger();

	ImGui::Begin("Assets", 0, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse);

	PrintFolders();

	Refresh();

	ImGui::End();

	ImGui::PopStyleColor(6);

	return UPDATE_CONTINUE;
}

update_status ModuleResources::PostUpdate(float dt)
{


	return UPDATE_CONTINUE;
}

bool ModuleResources::CleanUp()
{
	bool ret = true;


	//Delete physfs
	PHYSFS_deinit();

	return ret;
}


void ModuleResources::PathInfo(const char* path)
{
	char** assets = PHYSFS_enumerateFiles(path);

	ClearAssetsList();

	AddFolders(path, assets);

	PHYSFS_freeList(assets);
}


void ModuleResources::PrintFolders()
{

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::Button("New Folder")) {
			

			if (folderCounter == 0) {
				CreateFolder(NEW_FOLDER_PATH);
				folderCounter++;

			}
			else {
				string name = NEW_FOLDER_PATH2;
				name = name + (" ") + std::to_string(folderCounter) + ("/");
				const char* BChar = name.c_str();
				CreateFolder(BChar);
				folderCounter++;

			}


		}
		ImGui::Separator();
		if (ImGui::Button("<--")) {
			GoBackPath();
		}



		ImGui::EndMenuBar();
	}


	for (int i = 0; i < assetsList.size(); i++) {
		File AFile = assetsList[i];

		ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_FramePadding;

		
		bool TreeNodeEx = ImGui::TreeNodeEx((void*)(intptr_t)&AFile, treeNodeFlags, AFile.name.c_str());

		if (ImGui::IsItemHovered())
		{
			
			if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_::ImGuiMouseButton_Right))
			{
				DeleteFolder(AFile);
			}
			
			else if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_::ImGuiMouseButton_Left))
			{
				if (AFile.folder)
					SetNewPath(AFile.path.c_str());
			}
			

		}

		if (TreeNodeEx)
		{
			ImGui::TreePop();
		}
	
		ImGui::Separator();
	}

}



void ModuleResources::AddFolders(const char* path, char** assets)
{

	for (int i = 0; assets[i] != NULL; i++) {
		string Path = path;
		Path.append("/").append(assets[i]);
		File AFile(Path);
		assetsList.push_back(AFile);
		
	}
}

void ModuleResources::DeleteFolder(File path)
{
	PHYSFS_delete(path.name.c_str());
	refresh = true;

}

void ModuleResources::GoBackPath()
{
	SetNewPath(PATH_NAME);
}



#include "LevelEditor.h"
#include "Renderer.h"
#include "UserInput.h"
#include "Audio.h"
#include <fstream>
#include "TileSetSingleton.h"
#include <iostream>
#include <filesystem>
#include <ppltasks.h>
#include <sstream>
LevelEditor::LevelEditor(SceneManager* manager) : BaseScene(manager) { }

void LevelEditor::render()
{
	const auto timer = Engine::PreUpdate();
	input();

	switch (state)
	{
	case room_filepicker: RenderFilePicker(); break;
	case tile_editor: RenderTileEditor(); break;
	case object_editor: RenderObjectEditor(); break;
	case save_room: RenderSave(); break;
	}

	Engine::Render(timer);
}

void LevelEditor::RenderTileGrid()
{
	for (auto tile : tiles_on_grid_)
	{
		if (tile.tiletype == -1)
		{
			Engine::RenderEmptyTile(tile.x_pos, tile.y_pos, tile.width, tile.height);
		}
		else
		{
			Engine::RenderTile(tile.x_pos, tile.y_pos, tile.width, tile.height, TileSetSingleton::get_instance()->tiletypes[tile.tiletype][0],
				TileSetSingleton::get_instance()->tiletypes[tile.tiletype][1], TileSetSingleton::get_instance()->tilemap, 0.5);
		}
	}
}

void LevelEditor::RenderTileEditor()
{
	for (auto tile : tiles_in_toolbox_)
	{
		if (tile.tiletype == selected_tile_type_)
			Engine::RenderEmptyTile(tile.x_pos - 2, tile.y_pos - 2, tile.width + 8, tile.height + 8);

		Engine::RenderTile(tile.x_pos, tile.y_pos, k_tile_width_, k_tile_height_, TileSetSingleton::get_instance()->tiletypes[tile.tiletype][0],
			TileSetSingleton::get_instance()->tiletypes[tile.tiletype][1], TileSetSingleton::get_instance()->tilemap, 0.5);
	}

	RenderTileGrid();
}

void LevelEditor::RenderFilePicker()
{
	GetFiles();
	if (text_.length() > 0)
	{
		delete text_texture_;
		text_texture_ = Engine::LoadText("manaspc.ttf", 20, { 255, 196, 0, 255 }, text_.c_str());
	}
	int x = 100;
	int y = 50;
	for (auto file : file_names_)
	{
		Engine::RenderTexture(file, x, y, nullptr);
		x += 400;
		if (x > 950)
		{
			x = 100;
			y += 50;
		}
	}
	if (text_.length() > 0)
		Engine::RenderTexture(text_texture_, 450, 800, nullptr);
}

void LevelEditor::RenderObjectEditor()
{
	RenderTileGrid();

	for (int i = 0; i < objects_in_toolbox_.size(); ++i)
	{
		if (objects_in_toolbox_[i].name == objects_in_toolbox_[selected_object_].name)
			Engine::RenderEmptyTile(objects_in_toolbox_[i].x - 1, objects_in_toolbox_[i].y - 1, objects_in_toolbox_[i].width + 4, objects_in_toolbox_[i].height + 4);

		Engine::RenderTexture(objects_in_toolbox_[i].image, objects_in_toolbox_[i].x, objects_in_toolbox_[i].y, nullptr);
	}
	for (int i = 0; i < objects_on_grid_.size(); ++i)
	{
		Engine::RenderTexture(objects_on_grid_[i].image, objects_on_grid_[i].x, objects_on_grid_[i].y, nullptr);
	}
}

void LevelEditor::RenderSave()
{
	if (save_file_name_.length() > 0)
	{
		delete save_text_texture_;
		save_text_texture_ = Engine::LoadText("manaspc.ttf", 20, { 255, 196, 0, 255 }, save_file_name_.c_str());
	}
	auto save_text = Engine::LoadText("manaspc.ttf", 20, { 255, 196, 0, 255 }, "Please enter map name:");
	Engine::RenderTexture(save_text, 400, 300, nullptr);
	delete save_text;
	if (save_file_name_.length() > 0)
		Engine::RenderTexture(save_text_texture_, 450, 800, nullptr);
}

void LevelEditor::input()
{
	const int k_keydown = 0;
	const int k_keyup = 1;
	const int k_stop = 2;
	const int k_text = 3;

	auto inputs = Engine::GetInputs();

	//Quit if user wants to exit
	if (!std::get<k_stop>(inputs)) {
		is_running = false;
		return;
	}

	//Handle all key down events
	for (const auto& keycode : std::get<k_keydown>(inputs))
	{
		if (keycode == SDLK_ESCAPE)
		{
			scene_manager_->pop_scene(); scene_manager_->pop_scene();
		}

		switch (state)
		{
		case room_filepicker: InputFilePicker(keycode, std::get<k_text>(inputs)); break;
		case save_room: InputSave(keycode, std::get<k_text>(inputs)); break;
		case tile_editor: InputTileEditor(keycode); break;
		case object_editor: InputObjectEditor(keycode); break;
		}
	}

}

void LevelEditor::InputSave(SDL_Keycode keycode, std::string text)
{
	if (keycode == SDLK_BACKSPACE && text_.length() > 0)
		save_file_name_.pop_back();
	if (keycode == SDLK_RETURN)
		if (SaveFile())
		{
			state = room_filepicker;
			Engine::StartTextInput();
		}
	save_file_name_.append(text);
}

void LevelEditor::InputFilePicker(SDL_Keycode keycode, std::string text)
{
	if (keycode == SDLK_BACKSPACE && text_.length() > 0)
		text_.pop_back();
	if (keycode == SDLK_RETURN)
		if (OpenFile(text_))
		{
			state = tile_editor;
			Engine::StopTextInput();
		}
	text_.append(text);
}

void LevelEditor::InputTileEditor(SDL_Keycode keycode)
{
	if (keycode == k_lmb_)
	{
		//Select a Tile or Place a Tile
		auto mouse_pos = Engine::GetMouseState();
		if (mouse_pos.first > 1000)
		{
			SelectTile(mouse_pos.first, mouse_pos.second);
		}
		else
		{
			PlaceTile(mouse_pos.first, mouse_pos.second);
		}
	}
	if (keycode == SDLK_RETURN)
	{
		state = object_editor;
		Engine::StartTextInput();
	}
}

void LevelEditor::InputObjectEditor(SDL_Keycode keycode)
{
	if (keycode == k_lmb_)
	{
		//Select a Tile or Place a Tile
		auto mouse_pos = Engine::GetMouseState();
		if (mouse_pos.first > 1000)
		{
			SelectObject(mouse_pos.first, mouse_pos.second);
		}
		else
		{
			PlaceObject(mouse_pos.first, mouse_pos.second);
		}
	}
	if (keycode == SDLK_RETURN)
	{
		state = save_room;
		Engine::StartTextInput();
	}
}

void LevelEditor::SelectTile(int x, int y)
{
	for (auto tile : tiles_in_toolbox_)
	{
		if (x > tile.x_pos && x < tile.x_pos + (tile.width / 2) && y > tile.y_pos && y < tile.y_pos + (tile.height / 2))
		{
			selected_tile_type_ = tile.tiletype;
			return;
		}
	}
}

void LevelEditor::PlaceTile(int x, int y)
{
	for (int i = 0; i < tiles_on_grid_.size(); ++i)
	{
		if (x > tiles_on_grid_[i].x_pos && x < tiles_on_grid_[i].x_pos + (tiles_on_grid_[i].width / 2)
			&& y > tiles_on_grid_[i].y_pos && y < tiles_on_grid_[i].y_pos + (tiles_on_grid_[i].height / 2))
		{
			tiles_on_grid_[i].tiletype = selected_tile_type_;
			return;
		}
	}
}

void LevelEditor::SelectObject(int x, int y)
{
	for (int i = 0; i < objects_in_toolbox_.size(); ++i)
	{
		if (x > objects_in_toolbox_[i].x && x < objects_in_toolbox_[i].x + (objects_in_toolbox_[i].width / 2)
			&& y > objects_in_toolbox_[i].y && y < objects_in_toolbox_[i].y + (objects_in_toolbox_[i].height / 2))
		{
			selected_object_ = i;
			return;
		}
	}
}

void LevelEditor::PlaceObject(int x, int y)
{
	if (x > 150 && y > 150 && x < 790 - 24 && y < 630 - 24) {
		objects_on_grid_.push_back(EditorObject{
			objects_in_toolbox_[selected_object_].name,
			objects_in_toolbox_[selected_object_].file_path,
			objects_in_toolbox_[selected_object_].image,
			x,
			y,
			objects_in_toolbox_[selected_object_].width,
			objects_in_toolbox_[selected_object_].height
			});
	}
}

void LevelEditor::GetFiles()
{
	for (int i = file_names_.size() - 1; i >= 0; --i)
	{
		delete file_names_[i];
	}
	file_names_.clear();
	std::string path = "./assets/Levels";
	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		if (entry.path().extension().string() == ".map")
		{
			std::string filename = entry.path().filename().string();
			file_names_.push_back(Engine::LoadText("manaspc.ttf", 20, { 255, 196, 0, 255 }, filename.c_str()));
		}
	}
}

bool LevelEditor::SaveFile()
{
	//Open the map
	try {
		std::ofstream map("./assets/Levels/" + save_file_name_ + ".map");

		int counter = 0;
		//Go through the tiles
		for (int t = 0; t < k_total_tiles_; t++)
		{
			if (tiles_on_grid_[t].tiletype < 10)
				map << 0 << tiles_on_grid_[t].tiletype;
			else
				map << tiles_on_grid_[t].tiletype;
			if (counter < 19)
				map << " ";
			++counter;
			if (counter >= 20)
			{
				counter = 0;
				map << std::endl;
			}

		}

		//Close the file
		map.close();
	}
	catch (std::exception& e) {
		return false;
	}
	try {
		std::ofstream map("./assets/Levels/" + save_file_name_ + ".objects");

		//Go through the objects
		for (auto object : objects_on_grid_)
		{
			map << object.name << " " << (object.x - 150) * 2 << " " << (object.y - 150) * 2 << std::endl;
		}

		//Close the file
		map.close();
	}
	catch (std::exception& e) {
		return false;
	}
	return true;
}

void LevelEditor::cleanup()
{
	file_names_.clear();
	delete text_texture_;
	delete save_text_texture_;
}

bool LevelEditor::OpenFile(std::string path)
{
	if (path == "new")
	{
		CreateEmptyLevel();
		return true;
	}
	else {
		std::ifstream map("./assets/Levels/" + path);
		if (map.fail())
		{
			return false;
		}
		for (int i = 0; i < 300; ++i)
		{
			//Determines what kind of tile will be made
			int tile_type = -1;

			//Read tile from map file
			map >> tile_type;

			//If the was a problem in reading the map
			if (map.fail())
			{
				//Stop loading map	
				return false;
			}
			tiles_on_grid_[i].tiletype = tile_type;
		}
		map.close();

		path.erase(path.length() - 4);
		std::ifstream obj_map("./assets/Levels/" + path + ".objects");
		if (obj_map.fail())
		{
			return false;
		}

		std::string name;
		int x = -1, y = -1;

		std::stringstream buffer;
		buffer << obj_map.rdbuf();

		while (buffer.peek() >= 0) {
			if (!(buffer >> name)) {
				break;
			}
			if (!(buffer >> x)) {
				break;
			}
			if (!(buffer >> y)) {
				break;
			}

			for (int i = 0; i < objects_in_toolbox_.size(); ++i)
			{
				if (name == objects_in_toolbox_[i].name) {
					objects_on_grid_.push_back(EditorObject{
					objects_in_toolbox_[i].name,
					objects_in_toolbox_[i].file_path,
					objects_in_toolbox_[i].image,
					x/2+150,
					y/2+150,
					objects_in_toolbox_[i].width,
					objects_in_toolbox_[i].height
						});
					break;
				}
			}
		}

		obj_map.close();
	}
	return true;
}

void LevelEditor::CreateEmptyLevel()
{
	for (int i = 0; i < 300; ++i)
	{
		tiles_on_grid_[i].tiletype = 0;
	}
	objects_on_grid_.clear();
}

bool LevelEditor::init()
{
	if (TileSetSingleton::get_instance()->reload) {
		TileSetSingleton::get_instance()->tilemap = Engine::LoadTileset(TileSetSingleton::get_instance()->path);
		TileSetSingleton::get_instance()->reload = false;
	}
	tiles_on_grid_ = std::vector<TileComponent>();
	int x = 150;
	int y = 150;
	int counter = 0;
	for (int i = 0; i < 300; ++i)
	{
		tiles_on_grid_.push_back(TileComponent(x, y, k_tile_width_, k_tile_height_, 0));
		++counter;
		x += 32;
		if (counter >= 20)
		{
			x = 150;
			y += 32;
			counter = 0;
		}
	}

	x = 1180;
	y = 25;
	tiles_in_toolbox_ = std::vector<TileComponent>();
	for (int i = 0; i < TileSetSingleton::get_instance()->tiletypes.size(); ++i)
	{
		tiles_in_toolbox_.push_back(TileComponent(x, y, k_tile_width_, k_tile_height_, i));
		x += 40;
		if (x > 1230) {
			x = 1180;
			y += 40;
		}
	}
	GetFiles();
	InitObjects();
	Engine::StartTextInput();
	return true;
}

void LevelEditor::InitObjects()
{
	objects_in_toolbox_.push_back(EditorObject{
		"chest",
		"chest_full.png"
		});
	objects_in_toolbox_.push_back(EditorObject{
		"health_potion_small",
		"flask_red.png"
		});
	objects_in_toolbox_.push_back(EditorObject{
		"health_potion_large",
		"flask_big_red.png"
		});

	int x = 1140;
	int y = 25;
	for (int i = 0; i < objects_in_toolbox_.size(); ++i)
	{
		objects_in_toolbox_[i].x = x;
		objects_in_toolbox_[i].y = y;
		x += 60;
		if (x > 1230) {
			x = 1140;
			y += 50;
		}
		objects_in_toolbox_[i].image = Engine::LoadTileset("Sprites/" + objects_in_toolbox_[i].file_path);
	}
}

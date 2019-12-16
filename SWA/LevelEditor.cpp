#include "LevelEditor.h"
#include "Renderer.h"
#include "UserInput.h"
#include <fstream>
#include "TileSetSingleton.h"
#include <iostream>
#include <filesystem>
#include <ppltasks.h>
#include <sstream>
#include "SceneManager.h"
#include <Audio.h>
#include "Constants.h"

LevelEditor::LevelEditor(Engine::SceneManager* manager) : BaseScene(manager)
{}

void LevelEditor::render()
{
	const auto timer = Engine::pre_update();

	switch (state)
	{
	case room_filepicker: RenderRoomFilePicker(); break;
	case tile_editor: RenderTileEditor(); break;
	case object_editor: RenderObjectEditor(); break;
	case save_room: RenderRoomSave(); break;
	case mode_selection: RenderModeSelection();  break;
	case dungeon_filepicker: RenderDungeonFilepicker(); break;
	case dungeon_editor: RenderDungeonEditor(); break;
	case save_dungeon: RenderDungeonSave(); break;
	case exit_editor: scene_manager_->set_scene("mainmenu"); scene_manager_->delete_scene("leveleditor"); Engine::play_music("mainmenu.wav"); break;
	}

	Engine::render(timer);
	input();
}


void LevelEditor::RenderModeSelection()
{
	Engine::set_render_draw_color(255, 196, 0, 255);
	Engine::render_texture(menu_item_dungeon_.get(), Constants::k_window_width / 4 - 100, Constants::k_window_height / 2, nullptr);
	Engine::render_texture(menu_item_room_.get(), 3 * Constants::k_window_width / 4 - 100, Constants::k_window_height / 2, nullptr);
	Engine::render_line(Constants::k_window_width / 2, 0, Constants::k_window_width / 2, Constants::k_window_height);
}

void LevelEditor::RenderDungeonFilepicker()
{
	GetFiles("./assets/Levels/Dungeons", "dungeon");
	if (text_.length() > 0)
	{
		text_texture_ = std::unique_ptr<Texture>(Engine::load_text("manaspc.ttf", 20, { 255, 196, 0, 255 }, text_.c_str()));
	}
	int x = 100;
	int y = 50;
	for (auto& file : file_name_textures_)
	{
		Engine::render_texture(file.get(), x, y, nullptr);
		x += 400;
		if (x > 950)
		{
			x = 100;
			y += 50;
		}
	}
	if (text_.length() > 0)
		Engine::render_texture(text_texture_.get(), 450, 800, nullptr);
}

void LevelEditor::RenderDungeonEditor()
{
	GetFiles("./assets/Levels", "png");

	//Render toolbox
	int counter = 0;
	for (const auto& i : rooms_in_toolbox_)
	{
		Engine::render_tile(i.x, i.y, Engine::rect2d{ 0, 0,i.width * 4, i.height * 4, }, i.image.get(), 0.25);
		if (selected_room_template_ == counter) {
			Engine::set_render_draw_color(255, 255, 255, 255);
		}
		else
		{
			Engine::set_render_draw_color(0, 0, 0, 255);
		}
		Engine::draw_rectangle(Engine::rect2d{ i.x - 1, i.y - 1, i.width + 4, i.height + 4 });
		++counter;
	}

	//Render grid
	for (const auto& i : rooms_on_grid_)
	{
		if (!i.empty) {
			Engine::render_tile(i.x, i.y, Engine::rect2d{ 0, 0,i.width * 4, i.height * 4 }, i.image.get(), 0.25);
		}
		else {
			Engine::set_render_draw_color(255, 255, 255, 255);
			Engine::draw_rectangle(Engine::rect2d{ i.x, i.y, i.width, i.height });
		}
	}



}

void LevelEditor::RenderDungeonSave()
{
	if (save_file_name_.length() > 0)
	{
		save_text_texture_ = std::unique_ptr<Texture>(Engine::load_text("manaspc.ttf", 20, { 255, 196, 0, 255 }, save_file_name_.c_str()));
	}
	auto save_text = Engine::load_text("manaspc.ttf", 20, { 255, 196, 0, 255 }, "Please enter dungeon name:");
	Engine::render_texture(save_text, 400, 300, nullptr);
	delete save_text;
	if (save_file_name_.length() > 0)
		Engine::render_texture(save_text_texture_.get(), 450, 800, nullptr);
}

void LevelEditor::RenderTileGrid()
{
	for (const auto& tile : tiles_on_grid_)
	{
		if (tile.tiletype == -1)
		{
			Engine::set_render_draw_color(255, 255, 255, 255);
			Engine::draw_rectangle(Engine::rect2d{ tile.x_pos, tile.y_pos, tile.width, tile.height });
		}
		else
		{
			Engine::render_tile(tile.x_pos, tile.y_pos, Engine::rect2d{ TileSetSingleton::get_instance()->tiletypes[tile.tiletype][0],
				TileSetSingleton::get_instance()->tiletypes[tile.tiletype][1], tile.width, tile.height }, TileSetSingleton::get_instance()->tilemap, 0.5);
		}
	}
}

void LevelEditor::RenderTileEditor()
{
	for (const auto& tile : tiles_in_toolbox_)
	{
		Engine::render_tile(tile.x_pos, tile.y_pos, Engine::rect2d{ TileSetSingleton::get_instance()->tiletypes[tile.tiletype][0],
			TileSetSingleton::get_instance()->tiletypes[tile.tiletype][1],Constants::k_tile_width, Constants::k_tile_height }, TileSetSingleton::get_instance()->tilemap, 0.5);

		if (tile.tiletype == selected_tile_type_) {
			Engine::set_render_draw_color(255, 255, 255, 255);
			Engine::draw_rectangle(Engine::rect2d{ tile.x_pos - 2, tile.y_pos - 2, tile.width / 2 + 8, tile.height / 2 + 8 });
		}
	}
	RenderTileGrid();
}

void LevelEditor::RenderRoomFilePicker()
{
	GetFiles("./assets/Levels", "map");
	if (text_.length() > 0)
	{
		text_texture_ = std::unique_ptr<Texture>(Engine::load_text("manaspc.ttf", 20, { 255, 196, 0, 255 }, text_.c_str()));
	}
	int x = 100;
	int y = 50;
	for (auto& file : file_name_textures_)
	{
		Engine::render_texture(file.get(), x, y, nullptr);
		x += 400;
		if (x > 950)
		{
			x = 100;
			y += 50;
		}
	}
	if (text_.length() > 0)
		Engine::render_texture(text_texture_.get(), 450, 800, nullptr);
}

void LevelEditor::RenderObjectEditor()
{
	RenderTileGrid();

	for (auto& i : objects_in_toolbox_)
	{
		Engine::render_texture(i.image.get(), i.x, i.y, nullptr);

		if (i.name == objects_in_toolbox_[selected_object_].name) {
			Engine::set_render_draw_color(255, 255, 255, 255);
			Engine::draw_rectangle(Engine::rect2d{ i.x - 1, i.y - 1, i.width / 2 + 4, i.height / 2 + 4 });
		}
	}
	for (auto& i : objects_on_grid_)
	{
		Engine::render_texture(i.image.get(), i.x, i.y, nullptr);
	}
}

void LevelEditor::RenderRoomSave()
{
	if (save_file_name_.length() > 0)
	{
		save_text_texture_ = std::unique_ptr<Texture>(Engine::load_text("manaspc.ttf", 20, { 255, 196, 0, 255 }, save_file_name_.c_str()));
	}
	auto save_text = Engine::load_text("manaspc.ttf", 20, { 255, 196, 0, 255 }, "Please enter map name:");
	Engine::render_texture(save_text, 400, 300, nullptr);
	delete save_text;
	if (save_file_name_.length() > 0)
		Engine::render_texture(save_text_texture_.get(), 450, 800, nullptr);
}

void LevelEditor::input()
{
	const int k_keydown = 0;
	const int k_stop = 2;
	const int k_text = 3;

	auto inputs = Engine::GetInputs();

	if (!std::get<k_stop>(inputs)) {
		Engine::StopTextInput();
		is_running_ = false;
		return;

	}
	//Handle all key down events
	for (const auto& keycode : std::get<k_keydown>(inputs))
	{
		if (keycode == SDLK_ESCAPE)
		{
			Engine::stop_music();
			Engine::play_music("low.wav");
			std::this_thread::sleep_for(std::chrono::milliseconds(112));

			Engine::stop_music();
			scene_manager_->set_scene("mainmenu");
			Engine::play_music("mainmenu.wav");
			scene_manager_->delete_scene("leveleditor");
		}

		switch (state)
		{
		case room_filepicker: InputRoomFilePicker(keycode, std::get<k_text>(inputs)); break;
		case save_room: InputRoomSave(keycode, std::get<k_text>(inputs)); break;
		case tile_editor: InputTileEditor(keycode); break;
		case object_editor: InputObjectEditor(keycode); break;
		case mode_selection: InputModeSelection(keycode); break;
		case dungeon_filepicker: InputDungeonFilePicker(keycode, std::get<k_text>(inputs)); break;
		case dungeon_editor: InputDungeonEditor(keycode); break;
		case save_dungeon: InputDungeonSave(keycode, std::get<k_text>(inputs)); break;
		default:;
		}
	}

}

void LevelEditor::InputModeSelection(const int keycode)
{
	if (keycode == k_lmb_)
	{
		//Select which editor you want
		auto mouse_pos = Engine::GetMouseState();

		if (mouse_pos.first > Constants::k_window_width / 2)
			state = room_filepicker;
		else
			state = dungeon_filepicker;
	}
}

void LevelEditor::InputDungeonFilePicker(SDL_Keycode keycode, std::string& text)
{
	if (keycode == SDLK_BACKSPACE && text_.length() > 0)
		text_.pop_back();
	if (keycode == SDLK_RETURN)
		if (OpenDungeonFile(text_))
		{
			state = dungeon_editor;
			Engine::StopTextInput();
		}
	text_.append(text);
}

void LevelEditor::InputDungeonEditor(SDL_Keycode keycode)
{
	if (keycode == k_lmb_)
	{
		//Select a Tile or Place a Tile
		auto mouse_pos = Engine::GetMouseState();
		if (mouse_pos.first > 900)
		{
			SelectRoom(mouse_pos.first, mouse_pos.second);
		}
		else
		{
			PlaceRoom(mouse_pos.first, mouse_pos.second);
		}
	}
	if (keycode == SDLK_RETURN)
	{
		state = save_dungeon;
		save_file_name_.clear();
		Engine::StartTextInput();
	}
}

void LevelEditor::InputDungeonSave(SDL_Keycode keycode, std::string& text)
{
	if (keycode == SDLK_BACKSPACE && text_.length() > 0)
		save_file_name_.pop_back();
	if (keycode == SDLK_RETURN)
		if (SaveDungeonFile())
		{
			state = exit_editor;
			Engine::StartTextInput();
		}
	save_file_name_.append(text);
}

void LevelEditor::InputRoomSave(SDL_Keycode keycode, std::string& text)
{
	if (keycode == SDLK_BACKSPACE && text_.length() > 0)
		save_file_name_.pop_back();
	if (keycode == SDLK_RETURN)
		if (SaveRoomFile())
		{
			remove(("./assets/Levels/" + save_file_name_ + ".png").c_str());
			rename("./assets/Levels/temp_screenshot.png", ("./assets/Levels/" + save_file_name_ + ".png").c_str());
			state = exit_editor;
			Engine::StartTextInput();
		}
	save_file_name_.append(text);
}

void LevelEditor::InputRoomFilePicker(SDL_Keycode keycode, std::string& text)
{
	if (keycode == SDLK_BACKSPACE && text_.length() > 0)
		text_.pop_back();
	if (keycode == SDLK_RETURN)
		if (OpenRoomFile(text_))
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
		Engine::take_screenshot(640, 480, 150, 150, "./assets/Levels/temp_screenshot.png");
		Engine::StartTextInput();
	}
}

void LevelEditor::SelectTile(int x, int y)
{
	for (auto& tile : tiles_in_toolbox_)
	{
		if (x > tile.x_pos&& x < tile.x_pos + (tile.width / 2) && y > tile.y_pos&& y < tile.y_pos + (tile.height / 2))
		{
			selected_tile_type_ = tile.tiletype;
			return;
		}
	}
}

void LevelEditor::PlaceTile(int x, int y)
{
	for (auto& i : tiles_on_grid_)
	{
		if (x > i.x_pos&& x < i.x_pos + (i.width / 2)
			&& y > i.y_pos&& y < i.y_pos + (i.height / 2))
		{
			i.tiletype = selected_tile_type_;
			return;
		}
	}
}

void LevelEditor::SelectRoom(int x, int y)
{
	int counter = 0;
	for (auto& room : rooms_in_toolbox_)
	{
		if (x > room.x&& x < room.x + room.width && y > room.y&& y < room.y + room.height)
		{
			selected_room_template_ = counter;
			return;
		}
		++counter;
	}
}

void LevelEditor::PlaceRoom(int x, int y)
{
	if (selected_room_template_ == 0) {
		for (auto& j : rooms_on_grid_)
		{
			if (x > j.x&& x < j.x + j.width
				&& y > j.y&& y < j.y + j.height)
			{
				j.empty = true;;
				return;
			}
		}
		return;
	}
	for (auto& i : rooms_on_grid_)
	{
		if (x > i.x&& x < i.x + i.width
			&& y > i.y&& y < i.y + i.height)
		{
			i.name = rooms_in_toolbox_[selected_room_template_].name;
			i.file_path = rooms_in_toolbox_[selected_room_template_].file_path;
			i.image = rooms_in_toolbox_[selected_room_template_].image;
			i.empty = false;
			return;
		}
	}
}

void LevelEditor::SelectObject(int x, int y)
{
	for (auto i = 0; i < objects_in_toolbox_.size(); ++i)
	{
		if (x > objects_in_toolbox_[i].x&& x < objects_in_toolbox_[i].x + (objects_in_toolbox_[i].width / 2)
			&& y > objects_in_toolbox_[i].y&& y < objects_in_toolbox_[i].y + (objects_in_toolbox_[i].height / 2))
		{
			selected_object_ = i;
			return;
		}
	}
}

void LevelEditor::PlaceObject(int x, int y)
{
	if (x > 150 && y > 150 && x < 790 - 24 && y < 630 - 24) {
		if (selected_object_ == 0) {
			for (auto i = objects_on_grid_.begin(); i != objects_on_grid_.end(); ++i)
			{
				if (x > i->x&& x < i->x + (i->width / 2)
					&& y > i->y&& y < i->y + (i->height / 2))
				{
					objects_on_grid_.erase(i, i + 1);
					return;
				}
			}
			return;
		}
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

void LevelEditor::GetFiles(const char* path, const std::string extension)
{
	file_name_textures_.clear();
	file_names_.clear();
	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		if (entry.path().extension().string() == "." + extension)
		{
			std::string filename = entry.path().filename().string();
			file_names_.emplace_back(filename);
			file_name_textures_.push_back(std::unique_ptr<Texture>(Engine::load_text("manaspc.ttf", 20, { 255, 196, 0, 255 }, filename.c_str())));
		}
	}
}

bool LevelEditor::SaveDungeonFile()
{
	try {
		std::ofstream map("./assets/Levels/Dungeons/" + save_file_name_ + ".dungeon");

		int counter = 0;
		//Go through the rooms
		for (const auto& room : rooms_on_grid_)
		{
			if (!room.empty)
				map << room.name;
			else
				map << 0;
			if (counter < 4)
				map << " ";
			++counter;
			if (counter >= 5)
			{
				counter = 0;
				map << std::endl;
			}
		}
		//Close the file
		map.close();
	}
	catch (std::exception&) {
		return false;
	}

	return true;
}

bool LevelEditor::SaveRoomFile()
{
	//Open the map
	try {
		std::ofstream map("./assets/Levels/" + save_file_name_ + ".map");

		int counter = 0;
		//Go through the tiles
		for (int t = 0; t < Constants::k_total_tiles; t++)
		{
			if (tiles_on_grid_[t].tiletype < 10) {
				map << 0 << tiles_on_grid_[t].tiletype;
				if(tiles_on_grid_[t].tiletype == 8)
				{
					auto ladder_object = EditorObject{
						"ladder",
						"",
						nullptr,
						tiles_on_grid_[t].x_pos,
						tiles_on_grid_[t].y_pos,
						tiles_on_grid_[t].width,
						tiles_on_grid_[t].height,
					};
					objects_on_grid_.emplace_back(ladder_object);
				}
			}
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
	catch (std::exception&) {
		return false;
	}
	try {
		std::ofstream map("./assets/Levels/" + save_file_name_ + ".objects");

		//Go through the objects
		for (const auto& object : objects_on_grid_)
		{
			map << object.name << " " << (object.x - 150) * 2 << " " << (object.y - 150) * 2 << std::endl;
		}

		//Close the file
		map.close();
	}
	catch (std::exception&) {
		return false;
	}
	return true;
}

void LevelEditor::cleanup()
{
	file_name_textures_.clear();
	file_names_.clear();
}

bool LevelEditor::OpenDungeonFile(std::string& path)
{
	if (path == "new")
	{
		CreateEmptyDungeon();
		return true;
	}
	std::ifstream map("./assets/Levels/Dungeons/" + path);
	if (map.fail())
	{
		return false;
	}
	for (int i = 0; i < 25; ++i)
	{
		//Determines what kind of room will be made
		std::string room_name = "";

		//Read room name from map file
		map >> room_name;

		//If the was a problem in reading the map
		if (map.fail())
		{
			//Stop loading map	
			return false;
		}
		if (room_name != "0")
		{
			bool found = false;
			for (const auto& room : rooms_in_toolbox_)
			{
				if (room_name == room.name)
				{
					found = true;
					rooms_on_grid_[i].name = room.name;
					rooms_on_grid_[i].file_path = room.file_path;
					rooms_on_grid_[i].image = room.image;
					rooms_on_grid_[i].empty = false;
				}
			}
			if (!found)
				rooms_on_grid_[i].empty = true;
		}
		else
		{
			rooms_on_grid_[i].empty = true;
		}
	}
	map.close();
	return true;
}

bool LevelEditor::OpenRoomFile(std::string& path)
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

			for (auto& i : objects_in_toolbox_)
			{
				if (name == i.name) {
					objects_on_grid_.push_back(EditorObject{
						i.name,
						i.file_path,
						i.image,
					x / 2 + 150,
					y / 2 + 150,
						i.width,
						i.height
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

void LevelEditor::CreateEmptyDungeon()
{
	for (auto& i : rooms_on_grid_)
	{
		i.empty = true;
	}
}

bool LevelEditor::init()
{
	if (TileSetSingleton::get_instance()->reload) {
		TileSetSingleton::get_instance()->tilemap = Engine::load_tileset(TileSetSingleton::get_instance()->path);
		TileSetSingleton::get_instance()->reload = false;
	}
	tiles_on_grid_ = std::vector<TileComponent>();
	int x = 150;
	int y = 150;
	int counter = 0;
	for (int i = 0; i < 300; ++i)
	{
		tiles_on_grid_.emplace_back(x, y, Constants::k_tile_width, Constants::k_tile_height, 0);
		++counter;
		x += 32;
		if (counter >= 20)
		{
			x = 150;
			y += 32;
			counter = 0;
		}
	}

	x = 1140;
	y = 25;
	tiles_in_toolbox_ = std::vector<TileComponent>();
	for (unsigned int i = 0; i < TileSetSingleton::get_instance()->tiletypes.size(); ++i)
	{
		tiles_in_toolbox_.emplace_back(x, y, Constants::k_tile_width, Constants::k_tile_height, i);
		x += 40;
		if (x > 1230) {
			x = 1140;
			y += 40;
		}
	}

	GetFiles("./assets/Levels", "map");

	InitObjects();
	InitRoom();
	menu_item_dungeon_ = std::unique_ptr<Texture>(Engine::load_text("manaspc.ttf", 20, { 255, 196, 0, 255 }, "Dungeon Editor"));
	menu_item_room_ = std::unique_ptr<Texture>(Engine::load_text("manaspc.ttf", 20, { 255, 196, 0, 255 }, "Room Editor"));

	Engine::StartTextInput();
	return true;
}

void LevelEditor::InitObjects()
{
	objects_in_toolbox_.push_back(EditorObject{
		"delete",
		"delete.png"
		});
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
	for (auto& i : objects_in_toolbox_)
	{
		i.x = x;
		i.y = y;
		x += 60;
		if (x > 1230) {
			x = 1140;
			y += 50;
		}
		i.image = std::make_shared<Texture>(*Engine::load_tileset("Sprites/" + i.file_path));
	}
}

void LevelEditor::InitRoom()
{
	int x = 900;
	int y = 25;
	rooms_in_toolbox_ = std::vector<EditorObject>();
	rooms_in_toolbox_.push_back(EditorObject{
		"",
		"",
		std::make_shared<Texture>(*Engine::load_tileset("./Sprites/delete.png")),
		x,
		y,
		160,
		120
		});
	x += 170;
	for (auto& file_name : file_names_)
	{
		std::string name = file_name;
		name.erase(name.length() - 4);
		rooms_in_toolbox_.push_back(EditorObject{
			name,
			file_name,
			std::make_shared<Texture>(*Engine::load_tileset("Levels/" + name + ".png")),
			x,
			y,
			160,
			120
			});
		x += 170;
		if (x > 1180) {
			x = 900;
			y += 130;
		}
	}

	x = 50;
	y = 100;
	for (int i = 0; i < 25; ++i)
	{
		rooms_on_grid_.emplace_back(EditorObject{
			"",
			"",
			nullptr,
			x,
			y,
			160,
			120,
			true
			});
		x += 160;
		if (x > 700) {
			x = 50;
			y += 120;
		}
	}
}

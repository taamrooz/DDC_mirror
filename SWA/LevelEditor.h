#pragma once
#include "BaseScene.h"
#include "Texture.h"
#include "Animation.h"
#include "TileComponent.h"
#include "EditorObject.h"
#include "Renderer.h"

enum state
{
	mode_selection,
	dungeon_filepicker,
	room_filepicker,
	dungeon_editor,
	tile_editor,
	object_editor,
	save_room,
	save_dungeon
};
class LevelEditor :
	public BaseScene
{
private:
	state state = mode_selection;
	int selected_tile_type_ = 0;
	int selected_room_template_ = 0;
	std::vector<TileComponent> tiles_on_grid_;
	std::vector<TileComponent> tiles_in_toolbox_;
	std::vector<EditorObject> objects_on_grid_;
	std::vector<EditorObject> objects_in_toolbox_;
	std::vector<EditorObject> rooms_on_grid_;
	std::vector<EditorObject> rooms_in_toolbox_;
	std::string text_;
	std::string save_file_name_;
	std::vector<std::string> file_names_;
	std::vector<std::unique_ptr<Texture>> file_name_textures_;
	std::unique_ptr<Texture> text_texture_ = nullptr;
	std::unique_ptr<Texture> save_text_texture_ = nullptr;
	std::unique_ptr<Texture> menu_item_dungeon_ = nullptr;
	std::unique_ptr<Texture> menu_item_room_ = nullptr;
	constexpr static int k_screen_width_ = 1280;
	constexpr static int k_screen_height_ = 960;
	constexpr static int k_total_tiles_ = 300;
	constexpr static int k_tile_height_ = 64;
	constexpr static int k_tile_width_ = 64;
	constexpr static int k_total_sprites_ = 36;
	constexpr static int k_lmb_ = 1;
	constexpr static int k_rmb_ = 3;
	const std::string k_path_ = "Tileset.png";
	int selected_object_ = 0;
	void RenderTileGrid();
public:
	LevelEditor(SceneManager* manager);
	void RenderModeSelection();
	void RenderDungeonFilepicker();
	void RenderDungeonEditor();
	void RenderDungeonSave();
	void render();
	void RenderTileEditor();
	void RenderRoomFilePicker();
	void RenderObjectEditor();
	void RenderRoomSave();
	void InputModeSelection(SDL_Keycode keycode);
	void InputDungeonFilePicker(SDL_Keycode keycode, std::string text);
	void InputDungeonEditor(SDL_Keycode keycode);
	void InputDungeonSave(SDL_Keycode keycode, std::string text);
	void input();
	void InputRoomSave(SDL_Keycode keycode, std::string text);
	void InputRoomFilePicker(SDL_Keycode keycode, std::string text);
	void InputTileEditor(SDL_Keycode keycode);
	void SelectObject(int first, int second);
	void PlaceObject(int first, int second);
	void InputObjectEditor(SDL_Keycode keycode);
	void SelectTile(int x, int y);
	void PlaceTile(int x, int y);
	void SelectRoom(int x, int y);
	void PlaceRoom(int x, int y);
	void GetFiles(std::string path, std::string extension);
	bool SaveDungeonFile();
	void SaveScreenshot();
	bool SaveRoomFile();
	void cleanup();
	void CreateEmptyDungeon();
	bool OpenDungeonFile(std::string path);
	bool OpenRoomFile(std::string path);
	void CreateEmptyLevel();
	bool init();
	void InitObjects();
	void InitRoom();
};



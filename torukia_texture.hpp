#include <SDL2/SDL_image.h>

#include "torukia_engine.hpp"
#include "observer.hpp"

namespace Torukia {

class Animated_Texture;

class Entity_Manager : public observer<Entity_Manager, Animated_Texture, std::string>{

};

struct Frame {
	int w;			/**< wideness of a frame */
	int h;			/**< height of a frame */
};

class Base_Texture {
protected:
	std::string _id;

	SDL_Texture* _sdl_texture;
public:
	Base_Texture(SDL_Texture* sdl_texture, std::string id)
				: _sdl_texture(sdl_texture),
				  _id(id) {}

	void print_texture(SDL_Renderer* sdl_renderer, SDL_Rect* src_rect, SDL_Rect* dst_rect) {
		SDL_RenderCopy(sdl_renderer, _sdl_texture, src_rect, dst_rect);
	}
};

class Animated_Texture : public Base_Texture
						,public observable<Entity_Manager, Animated_Texture, std::string> {
protected:
	int _time_tick;			/**< _time_tick for animation purpos */
	int _animation_speed;

	bool _is_animated;		/**< if animation is actif */

	bool _loop_animation;	/**< if the animation is looped */

	int _current_frame; 	/**< 0 is the begening of the animation */
	int _range[2];      	/**< the range of the animation set frames */

public:
	Animated_Texture(SDL_Texture* sdl_texture, std::string id, Entity_Manager& manager, int animation_speed)
								: Base_Texture(sdl_texture, id),
								  _time_tick(0),
								  _animation_speed(animation_speed),
								  _is_animated(false),
								  _loop_animation(false),
								  _current_frame(0),
								  _range{0,0}
	{
		this->observable<Entity_Manager, Animated_Texture, std::string>::add_observer(manager);
	}

	void print(int x, int y);
	/** @fn void set_range(int range[])
	 *	
	 *  You will need to use enumeration to specify range
	 */
	void set_range(int range[]);
};

class Factory_Texture {
protected:
	SDL_Renderer* _sdl_renderer;
	SDL_Texture* _sdl_texture;

	Frame _asset_dimentions;

	std::string _asset_path;

	bool _is_loaded;
public:
	Factory_Texture(SDL_Renderer* sdl_renderer, std::string asset_path) 
				: 	_sdl_renderer(sdl_renderer),
					_asset_path(asset_path),
					_sdl_texture(IMG_LoadTexture(_sdl_renderer,_asset_path.c_str()))

	{
		SDL_QueryTexture(_sdl_texture, NULL, NULL, &_asset_dimentions.w, &_asset_dimentions.h);
	}
	Frame get_asset_dimentions();
};

Frame Factory_Texture::get_asset_dimentions() {
	return _asset_dimentions;
}

class Factory_Animation : public Factory_Texture {
protected:
	Frame _frames_size;
	int _default_animation_speed;
public:
	Factory_Animation(SDL_Renderer* sdl_renderer, 
						std::string path, 
						int frame_w, 
						int frame_h,
						int default_animation_speed)
						: Factory_Texture(sdl_renderer, path),
						  _frames_size{frame_w, frame_h},
						  _default_animation_speed(default_animation_speed) 
	{}

	Frame get_frames_size();
	int get_default_animation_speed();
	Animated_Texture&& make(std::string id, Entity_Manager& manager);
};

Frame Factory_Animation::get_frames_size(){
	return _frames_size;
}

int Factory_Animation::get_default_animation_speed() {
	return _default_animation_speed;
}

Animated_Texture&& Factory_Animation::make(std::string id, Entity_Manager& manager) {
	Animated_Texture animated_texture(_sdl_texture, id, manager, _default_animation_speed);
	return std::move( animated_texture);
}

} /* namespace Torukia */
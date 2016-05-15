#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModuleEffects.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"

#include "SDL/include/SDL_timer.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleEffects::ModuleEffects()
{
	graphics = NULL;
	effect1 = NULL;
	effect2 = NULL;
	effect3 = NULL;

	position.x = 100;
	position.y = 200;

	god.PushBack({ 248, 47, 38, 38 });
	god.PushBack({ 286, 47, 38, 38 });
	god.PushBack({ 324, 47, 38, 38 });
	god.PushBack({ 362, 47, 38, 38 });
	god.loop = true;
	god.speed = 0.2f;

	bomb.PushBack({ 0, 341, 240, 320 });
	bomb.PushBack({ 240, 341, 240, 320 });
	bomb.PushBack({ 480, 341, 240, 320 });
	bomb.PushBack({ 720, 341, 240, 320 });
	bomb.PushBack({ 960, 341, 240, 320 });
	bomb.PushBack({ 1200, 341, 240, 320 });
	bomb.PushBack({ 0, 661, 240, 320 });
	bomb.PushBack({ 240, 661, 240, 320 });
	bomb.PushBack({ 480, 661, 240, 320 });
	bomb.PushBack({ 720, 661, 240, 320 });
	bomb.PushBack({ 960, 661, 240, 320 });
	bomb.PushBack({ 1200, 661, 240, 320 });
	bomb.PushBack({ 0, 981, 240, 320 });
	bomb.PushBack({ 240, 981, 240, 320 });
	bomb.PushBack({ 480, 981, 240, 320 });
	bomb.PushBack({ 720, 981, 240, 320 });
	bomb.PushBack({ 960, 981, 240, 320 });
	bomb.loop = true;
	bomb.speed = 0.5f;

	goahead.PushBack({ 198, 87, 50, 48 });
	goahead.PushBack({ 0, 0, 1, 1 });
	goahead.loop = true;
	goahead.speed = 0.1f;

}

ModuleEffects::~ModuleEffects()
{}

// Load assets
bool ModuleEffects::Start()
{
	LOG("Loading effects");

	graphics = App->textures->Load("Outzone/particle.png");

	position.x = App->player->position.x;
	position.y = App->player->position.y;

	return true;
}

// Unload assets
bool ModuleEffects::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

update_status ModuleEffects::Update()
{
	//god
	if ((App->player->Invencible == true) || (App->player->Superspeed == true) || (App->player->Fly == true)){
		godcurrenttime = SDL_GetTicks();
		if (godcurrenttime > (godactiontime + 400)){
			effect1 = &god;
			godactiontime = godcurrenttime;
		}
	}
	else{
		effect1 = NULL;
	}
	position = App->player->position;
	if (effect1 != nullptr){
		App->render->Blit(graphics, position.x, position.y, &(effect1->GetCurrentFrame()));
	}
	
	//bomb
	bombcurrenttime = SDL_GetTicks();
	if (App->input->keyboard[SDL_SCANCODE_X] == KEY_STATE::KEY_DOWN)
	{
		if (bombactive == false){
			bombactive = true;
			effect2collider = App->collision->AddCollider({ App->render->camera.x, App->render->camera.y / 2, 240, 340 }, COLLIDER_BOMB);
			bombactiontime = SDL_GetTicks();
		}
	}
	if (bombcurrenttime > (bombactiontime + 700)){
		bombactive = false;
		App->collision->EraseCollider(effect2collider);
	}
	if (bombactive == true){
		effect2 = &bomb;
		effect2collider->SetPos(App->render->camera.x, App->render->camera.y / 2);
	}
	else{
		effect2 = NULL;
	}
	if (effect2 != nullptr){
		App->render->Blit(graphics, App->render->camera.x, App->render->camera.y / 2, &(effect2->GetCurrentFrame()));
	}
	
	//go ahead
	goaheadcurrenttime = SDL_GetTicks();

	if ((App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE) 
		|| (App->player->position.y >= (170 + (App->render->camera.y / 2)))){

		if (goaheadfirstloop == true){
			goaheadactiontime = SDL_GetTicks();
			goaheadfirstloop = false;
		}

		if (goaheadcurrenttime > (goaheadactiontime + 5000)){
			effect3 = &goahead;
			goaheadactiontime = goaheadcurrenttime;
		}
	}
	else{
		effect3 = NULL;
		goaheadfirstloop = true;
	}
	if (effect3 != nullptr){
		App->render->Blit(graphics, App->render->camera.x + 95, (App->render->camera.y / 2) + 80, &(effect3->GetCurrentFrame()));
	}

	return UPDATE_CONTINUE;
}
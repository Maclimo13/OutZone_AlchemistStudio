#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"

#include "SDL/include/SDL_timer.h"

#define PLAYER_MULTIPLE_SHOOT_DELAY 750
#define SHOOTDELAY 125

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{
	graphics = NULL;
	current_animation = NULL;

	position.x = 100;
	position.y = 200;

	// idle animation
	idle_w.PushBack({ 24, 343, 29, 38 });
	idle_wa.PushBack({ 58, 79, 29, 36 });
	idle_wd.PushBack({ 19, 24, 27, 36 });
	idle_a.PushBack({ 21, 137, 28, 33 });
	idle_s.PushBack({ 191, 285, 31, 39 });
	idle_sa.PushBack({ 63, 187, 30, 37 });
	idle_sd.PushBack({ 27, 238, 28, 37 });
	idle_d.PushBack({ 61, 25, 27, 35 });
	//MOVEMENT
	// move upwards
	up.PushBack({ 65, 344, 27, 37 });
	up.PushBack({ 102, 344, 27, 37 });
	up.PushBack({ 138, 344, 26, 37 });
	up.PushBack({ 173, 344, 28, 37 });
	up.loop = true;
	up.speed = 0.1f;

	// Move down
	down.PushBack({ 191, 285, 31, 39 });
	down.PushBack({ 234, 285, 28, 39 });
	down.PushBack({ 274, 287, 27, 37 });
	down.PushBack({ 316, 285, 28, 39 });
	down.loop = true;
	down.speed = 0.1f;
	//left
	left.PushBack({ 21, 137, 28, 33 });
	left.PushBack({ 59, 135, 28, 35 });
	left.PushBack({ 97, 135, 29, 35 });
	left.PushBack({ 136, 135, 27, 35 });
	left.PushBack({ 173, 135, 29, 35 });
	left.loop = true;
	left.speed = 0.1f;
	//right
	right.PushBack({ 61, 25, 27, 35 });
	right.PushBack({ 103, 25, 25, 36 });
	right.PushBack({ 138, 26, 28, 35 });
	right.PushBack({ 176, 24, 26, 37 });
	right.PushBack({ 212, 26, 29, 35 });
	right.loop = true;
	right.speed = 0.1f;
	//Diagonal right top
	Drightop.PushBack({ 209, 79, 28, 40 });
	Drightop.PushBack({ 238, 75, 27, 42 });
	Drightop.PushBack({ 270, 74, 30, 41 });
	Drightop.PushBack({ 305, 75, 26, 40 });
	Drightop.loop = true;
	Drightop.speed = 0.1f;
	//Diagonal left top
	Lefthtop.PushBack({ 320, 216, 33, 40 });
	Lefthtop.PushBack({ 355, 215, 35, 42 });
	Lefthtop.PushBack({ 390, 215, 33, 42 });
	Lefthtop.PushBack({ 425, 212, 33, 38 });
	Lefthtop.loop = true;
	Lefthtop.speed = 0.1f;
	//Diagonal right bot
	Drighbot.PushBack({ 265, 140, 33, 44 });
	Drighbot.PushBack({ 295, 143, 33, 41 });
	Drighbot.PushBack({ 331, 143, 34, 44 });
	Drighbot.PushBack({ 365, 143, 34, 44 });
	Drighbot.PushBack({ 401, 143, 32, 44 });
	Drighbot.loop = true;
	Drighbot.speed = 0.1f;
	//Diagonal left bot
	Lefthbot.PushBack({ 117, 187, 30, 36 });
	Lefthbot.PushBack({ 150, 188, 31, 38 });
	Lefthbot.PushBack({ 188, 188, 31, 39 });
	Lefthbot.PushBack({ 225, 190, 28, 37 });
	Lefthbot.loop = true;
	Lefthbot.speed = 0.1f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("Outzone/playermovement2.png");

	destroyed = false;
	position.x = 105;
	position.y = 250;

	playercollision = App->collision->AddCollider({ position.x, position.y + 2, 28, 30 }, COLLIDER_PLAYER, this);

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);
	App->collision->EraseCollider(playercollision);

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	int speed = 0;
	PreviousPos = position;

	if (Superspeed == true){
		speed = 12;
	}
	else{
		speed = 4;
	}
	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT){
		if (App->player->position.y <= (160 + (App->render->camera.y / 2))){
			App->render->camera.y -= speed;
		}
		
	}

	if (Superspeed == true){
		speed = 3;
	}
	else{
		speed = 1;
	}

	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		if ((position.x -= speed) <= 0){
			position.x = 0;
		}
		if (collisionWallS == true)
		{
			position.x = PreviousPos.x;
			collisionWallS = false;
		}
		else{
			position.x -= speed;
		}
		if (current_animation != &left)
		{
			left.Reset();
			current_animation = &left;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		if ((position.x += speed) >= 215){
			position.x = 215;
		}
		if (collisionWallS == true)
		{
			position.x = PreviousPos.x;
			collisionWallS = false;
		}
		else{
			position.x += speed;
		}
		current_animation = &right;
		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT){
			current_animation = &idle_w;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
		if (collisionWallT == true)
		{
			position.y = PreviousPos.y;
			collisionWallT = false;
		}
		if ((position.y += speed) >= (280 + (App->render->camera.y / 2))){
			position.y = (280 + (App->render->camera.y / 2));
		}
		else{
			position.y += speed;
		}

		current_animation = &down;

		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT){
			if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT){
				current_animation = &down;
			}
			else{
				current_animation = &Drighbot;
			}
		}
		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT){
			if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT){
				current_animation = &down;
			}
			else{
				current_animation = &Lefthbot;
			}
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	{
		if ((position.y -= speed) <= -3160){
			position.y = -3160;
		}
		if (collisionWallT == true)
		{
			position.y = PreviousPos.y;
			collisionWallT = false;
		}
		else{
			position.y -= speed;
		}

		//if (current_animation != &up)
		//{
		//	up.Reset();
		if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT){
			current_animation = &idle_w;
		}
		else{
			current_animation = &up;
		}

		//}
		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT){
			if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT){
				current_animation = &up;
			}
			else{
				current_animation = &Drightop;
			}
		}
		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT){
			if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT){
				current_animation = &up;
			}
			else{
				current_animation = &Lefthtop;
			}
		}
	}

	// A
	if ((App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT) && (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE) && (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE) && (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE))
	{
		if (lastkeypressed != LAST_KEY_A){
			beforelastkeypressed = (BEFORE_LAST_KEY)lastkeypressed;
			playeractiontime = SDL_GetTicks();
		}
		lastkeypressed = LAST_KEY::LAST_KEY_A;
	}

	// D
	if ((App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT) && (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE) && (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE) && (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE))
	{
		if (lastkeypressed != LAST_KEY_D){
			beforelastkeypressed = (BEFORE_LAST_KEY)lastkeypressed;
			playeractiontime = SDL_GetTicks();
		}
		lastkeypressed = LAST_KEY::LAST_KEY_D;
	}

	// S / ASD
	if (((App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT) && (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE) && (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE) && (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE)) || ((App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT) && (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT) && (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE) && (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)))
	{
		if (lastkeypressed != LAST_KEY_S){
			beforelastkeypressed = (BEFORE_LAST_KEY)lastkeypressed;
			playeractiontime = SDL_GetTicks();
		}
		lastkeypressed = LAST_KEY::LAST_KEY_S;
	}

	// SD
	if ((App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT) && (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT) && (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE) && (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE)){
		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT){
		}
		else{
			if (lastkeypressed != LAST_KEY_SD){
				beforelastkeypressed = (BEFORE_LAST_KEY)lastkeypressed;
				playeractiontime = SDL_GetTicks();
			}
			lastkeypressed = LAST_KEY::LAST_KEY_SD;
		}
	}

	// SA
	if ((App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT) && (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT) && (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE) && (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE)){
		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT){
		}
		else{
			if (lastkeypressed != LAST_KEY_SA){
				beforelastkeypressed = (BEFORE_LAST_KEY)lastkeypressed;
				playeractiontime = SDL_GetTicks();
			}
			lastkeypressed = LAST_KEY::LAST_KEY_SA;
		}
	}

	// W / AWD
	if (((App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT) && (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE) && (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE) && (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE)) || ((App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE) && (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT) && (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT) && (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)))
	{
		lastkeypressed = LAST_KEY::LAST_KEY_W;
	}

	// WD
	if ((App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT) && (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT) && (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE) && (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE)){
		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT){
		}
		else{
			if (lastkeypressed != LAST_KEY_WD){
				beforelastkeypressed = (BEFORE_LAST_KEY)lastkeypressed;
				playeractiontime = SDL_GetTicks();
			}
			lastkeypressed = LAST_KEY::LAST_KEY_WD;
		}
	}

	// WA
	if (((App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT) && (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT) && (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE) && (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE))){
		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT){
		}
		else{
			if (lastkeypressed != LAST_KEY_WA){
				beforelastkeypressed = (BEFORE_LAST_KEY)lastkeypressed;
				playeractiontime = SDL_GetTicks();
			}
			lastkeypressed = LAST_KEY::LAST_KEY_WA;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_F2] == KEY_STATE::KEY_DOWN){
		Invencible = true;
	}
	
	if (App->input->keyboard[SDL_SCANCODE_F3] == KEY_STATE::KEY_DOWN){
		Invencible = false;
	}

	if (App->input->keyboard[SDL_SCANCODE_F4] == KEY_STATE::KEY_DOWN){
		Superspeed = true;
	}

	if (App->input->keyboard[SDL_SCANCODE_F5] == KEY_STATE::KEY_DOWN){
		Superspeed = false;
	}

	if (App->input->keyboard[SDL_SCANCODE_F6] == KEY_STATE::KEY_DOWN){
		Fly = true;
	}

	if (App->input->keyboard[SDL_SCANCODE_F7] == KEY_STATE::KEY_DOWN){
		Fly = false;
	}

	// AD
	if ((App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT) && (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE) && (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE) && (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT))
	{
		lastkeypressed = LAST_KEY::LAST_KEY_W;
	}

	// WS
	if ((App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE) && (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT) && (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT) && (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE))
	{
		lastkeypressed = LAST_KEY::LAST_KEY_W;
	}

	//WSD
	if ((App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE) && (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT) && (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT) && (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT))
	{
		lastkeypressed = LAST_KEY::LAST_KEY_WD;
	}

	//WAS
	if ((App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT) && (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT) && (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT) && (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE))
	{
		lastkeypressed = LAST_KEY::LAST_KEY_WA;
	}

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_REPEAT)
	{
		shootcurrenttime = SDL_GetTicks();
		playercurrenttime = SDL_GetTicks();

		if (shootcurrenttime > (shootactiontime + SHOOTDELAY)){
			if (lastkeypressed == LAST_KEY_W){
				App->particles->AddParticle(App->particles->laser0, position.x + 18, position.y, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->laserweaponshoot0, position.x + 13, position.y - 13);
			}
			else if (lastkeypressed == LAST_KEY_A){
				App->particles->AddParticle(App->particles->laser270, position.x - 2, position.y + 5, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->laserweaponshoot270, position.x - 12, position.y + 2);
			}
			else if (lastkeypressed == LAST_KEY_S){
				App->particles->AddParticle(App->particles->laser180, position.x + 5, position.y + 13, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->laserweaponshoot180, position.x + 1, position.y + 23);
			}
			else if (lastkeypressed == LAST_KEY_D){
				App->particles->AddParticle(App->particles->laser90, position.x + 15, position.y + 10, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->laserweaponshoot90, position.x + 25, position.y + 4);
			}
			else if (lastkeypressed == LAST_KEY_WA){
				if (playercurrenttime < (playeractiontime + PLAYER_MULTIPLE_SHOOT_DELAY)) {
					if (beforelastkeypressed == LAST_KEY_W){
						App->particles->AddParticle(App->particles->laser337_5, position.x + 2, position.y - 6, COLLIDER_PLAYER_SHOT);
						beforelastkeypressed = BEFORE_LAST_KEY::NO_KEY_PRESSED_BEFORE;
					}
					else if (beforelastkeypressed == LAST_KEY_A){
						App->particles->AddParticle(App->particles->laser292_5, position.x + 2, position.y - 6, COLLIDER_PLAYER_SHOT);
						beforelastkeypressed = BEFORE_LAST_KEY::NO_KEY_PRESSED_BEFORE;
					}
					playeractiontime = playercurrenttime;
				}
				App->particles->AddParticle(App->particles->laser315, position.x + 2, position.y - 6, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->laserweaponshoot315, position.x, position.y - 10);
			}
			else if (lastkeypressed == LAST_KEY_WD){
				if (playercurrenttime < (playeractiontime + PLAYER_MULTIPLE_SHOOT_DELAY)) {
					if (beforelastkeypressed == LAST_KEY_W){
						App->particles->AddParticle(App->particles->laser22_5, position.x + 17, position.y - 1, COLLIDER_PLAYER_SHOT);
						beforelastkeypressed = BEFORE_LAST_KEY::NO_KEY_PRESSED_BEFORE;
					}
					else if (beforelastkeypressed == LAST_KEY_D){
						App->particles->AddParticle(App->particles->laser67_5, position.x + 17, position.y - 1, COLLIDER_PLAYER_SHOT);
						beforelastkeypressed = BEFORE_LAST_KEY::NO_KEY_PRESSED_BEFORE;
					}
					playeractiontime = playercurrenttime;
				}
				App->particles->AddParticle(App->particles->laser45, position.x + 17, position.y - 1, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->laserweaponshoot45, position.x + 23, position.y - 8);
			}
			else if (lastkeypressed == LAST_KEY_SA){
				if (playercurrenttime < (playeractiontime + PLAYER_MULTIPLE_SHOOT_DELAY)) {
					if (beforelastkeypressed == LAST_KEY_S){
						App->particles->AddParticle(App->particles->laser202_5, position.x - 1, position.y + 7, COLLIDER_PLAYER_SHOT);
						beforelastkeypressed = BEFORE_LAST_KEY::NO_KEY_PRESSED_BEFORE;
					}
					else if (beforelastkeypressed == LAST_KEY_A){
						App->particles->AddParticle(App->particles->laser247_5, position.x - 1, position.y + 7, COLLIDER_PLAYER_SHOT);
						beforelastkeypressed = BEFORE_LAST_KEY::NO_KEY_PRESSED_BEFORE;
					}
					playeractiontime = playercurrenttime;
				}
				App->particles->AddParticle(App->particles->laser225, position.x - 1, position.y + 7, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->laserweaponshoot225, position.x - 8, position.y + 13);
			}
			else if (lastkeypressed == LAST_KEY_SD){
				if (playercurrenttime < (playeractiontime + PLAYER_MULTIPLE_SHOOT_DELAY)) {
					if (beforelastkeypressed == LAST_KEY_S){
						App->particles->AddParticle(App->particles->laser112_5, position.x + 10, position.y + 10, COLLIDER_PLAYER_SHOT);
						beforelastkeypressed = BEFORE_LAST_KEY::NO_KEY_PRESSED_BEFORE;
					}
					else if (beforelastkeypressed == LAST_KEY_D){
						App->particles->AddParticle(App->particles->laser157_5, position.x + 10, position.y + 10, COLLIDER_PLAYER_SHOT);
						beforelastkeypressed = BEFORE_LAST_KEY::NO_KEY_PRESSED_BEFORE;
					}
					playeractiontime = playercurrenttime;
				}
				App->particles->AddParticle(App->particles->laser135, position.x + 10, position.y + 10, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->laserweaponshoot135, position.x + 15, position.y + 15);
			}
			shootactiontime = shootcurrenttime;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_X] == KEY_STATE::KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->bomb, App->render->camera.x/2, App->render->camera.y/2, COLLIDER_BOMB);
	}

	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE){

		playertime = SDL_GetTicks();

		if (lastkeypressed == LAST_KEY_W){
			current_animation = &idle_w;
		}
		else if (lastkeypressed == LAST_KEY_A){
			current_animation = &idle_a;
		}
		else if (lastkeypressed == LAST_KEY_S){
			current_animation = &idle_s;
		}
		else if (lastkeypressed == LAST_KEY_D){
			current_animation = &idle_d;
		}
		else if (lastkeypressed == LAST_KEY_WA){
			current_animation = &idle_wa;
		}
		else if (lastkeypressed == LAST_KEY_WD){
			current_animation = &idle_wd;
		}
		else if (lastkeypressed == LAST_KEY_SA){
			current_animation = &idle_sa;
		}
		else if (lastkeypressed == LAST_KEY_SD){
			current_animation = &idle_sd;
		}
		else{
			current_animation = &idle_w;
		}

		if (playertime > (playerinitialtime + 7000)) {
			App->particles->AddParticle(App->particles->goahead, (App->render->camera.x / 2) + 95, (App->render->camera.y / 2) + 60);
			playerinitialtime = playertime;
		}

	}

	playercollision->SetPos(position.x, (position.y + 2));

	// Draw everything --------------------------------------
	if (current_animation == nullptr){
	}
	else{
		if (collisionPrint == true)
		{
			App->render->Blit(graphics, PreviousPos.x, PreviousPos.y, &(current_animation->GetCurrentFrame()));
			//collisionPrint = false;
		}
		else
		{

			App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

		}
	}
		
	

	return UPDATE_CONTINUE;
}


void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (Fly == false){
		if (c1 == playercollision && destroyed == false && App->fade->IsFading() == false)
		{
			if (c2->type == COLLIDER_WALL)
			{
				int speed = 1;
				int height;
				if ((((c2->rect.y) + c2->rect.h) <= c1->rect.y + 2))
				{
					position = PreviousPos;
					collisionWallT = true;
				}
				else if (((c2->rect.x + c2->rect.w) <= c1->rect.x + 1) || ((c1->rect.x + c1->rect.w) >= c2->rect.x + 1))
				{
					position = PreviousPos;
					collisionWallS = true;
				}
			}
			else if (c2->type == COLLIDER_WALL)
			{
				int height;
				if ((((c2->rect.y) + c2->rect.h) <= c1->rect.y + 2))
				{
					position = PreviousPos;
					collisionWallT = true;
				}
				else if (((c2->rect.x + c2->rect.w) <= c1->rect.x + 1) || ((c1->rect.x + c1->rect.w) >= c2->rect.x + 1))
				{
					position = PreviousPos;
					collisionWallS = true;
				}
			}
			else{
				if (Invencible == false){
					App->player->Disable();
					App->particles->AddParticle(App->particles->playerexplosion, position.x - 47, position.y - 54, COLLIDER_NONE);
					App->fade->FadeToBlack((Module*)App->scene_space, (Module*)App->scene_gameover);
					destroyed = true;
				}
			}
		}
	}
}
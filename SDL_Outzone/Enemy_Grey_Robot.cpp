#include "Application.h"
#include "Enemy_Turret1.h"
#include"Enemy_Grey_Robot.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "SDL/include/SDL_timer.h"
#include <math.h>

#define RANGE 30
#define PI 3.14159265
#define ANGLE_CONVERT (180.0 / PI)
#define ANGLE_CONVERT_REVERSE (PI / 180.0)
#define ENEMY_SHOOT_SPEED 4
#define ENEMYSHOOTDELAY 2500

Enemy_GreyRobot::Enemy_GreyRobot(int x, int y) : Enemy(x, y)
{
	live = 100;
	GRobot__0.PushBack({ 280, 0, 40, 40 });
	GRobot__22_5.PushBack({ 280, 40, 40, 40 });
	GRobot__45.PushBack({ 240, 40, 40, 40 });
	GRobot__67_5.PushBack({ 200, 40, 40, 40 });
	GRobot__90.PushBack({ 160, 40, 40, 40 });
	GRobot__112_5.PushBack({ 120, 40, 40, 40 });
	GRobot__135.PushBack({ 80, 40, 40, 40 });
	GRobot__157_5.PushBack({ 40, 40, 40, 40 });
	GRobot__180.PushBack({ 0, 40, 40, 40 });
	GRobot__202_5.PushBack({ 0, 0, 40, 40 });
	GRobot__225.PushBack({ 40, 0, 40, 40 });
	GRobot__247_5.PushBack({ 80, 0, 40, 40 });
	GRobot__270.PushBack({ 120, 0, 40, 40 });
	GRobot__292_5.PushBack({ 160, 0, 40, 40 });
	GRobot__315.PushBack({ 200, 0, 40, 40 });
	GRobot__337_5.PushBack({ 240, 0, 40, 40 });

	GRobot__w.PushBack({ 160, 200, 40, 40 });
	GRobot__w.PushBack({ 200, 200, 40, 40 });
	GRobot__w.PushBack({ 240, 200, 40, 40 });
	GRobot__w.PushBack({ 280, 200, 40, 40 });
	GRobot__w.loop = true;
	GRobot__w.speed = 0.1f;

	GRobot__wa.PushBack({ 160, 80, 40, 40 });
	GRobot__wa.PushBack({ 200, 80, 40, 40 });
	GRobot__wa.PushBack({ 240, 80, 40, 40 });
	GRobot__wa.PushBack({ 280, 80, 40, 40 });
	GRobot__wa.loop = true;
	GRobot__wa.speed = 0.1f;

	GRobot__wd.PushBack({ 0, 80, 40, 40 });
	GRobot__wd.PushBack({ 40, 80, 40, 40 });
	GRobot__wd.PushBack({ 80, 80, 40, 40 });
	GRobot__wd.PushBack({ 120, 80, 40, 40 });
	GRobot__wd.loop = true;
	GRobot__wd.speed = 0.1f;

	GRobot__a.PushBack({ 160, 120, 40, 40 });
	GRobot__a.PushBack({ 200, 120, 40, 40 });
	GRobot__a.PushBack({ 240, 120, 40, 40 });
	GRobot__a.PushBack({ 280, 120, 40, 40 });
	GRobot__a.loop = true;
	GRobot__a.speed = 0.1f;

	GRobot__s.PushBack({ 0, 200, 40, 40 });
	GRobot__s.PushBack({ 40, 200, 40, 40 });
	GRobot__s.PushBack({ 80, 200, 40, 40 });
	GRobot__s.PushBack({ 120, 200, 40, 40 });
	GRobot__s.loop = true;
	GRobot__s.speed = 0.1f;

	GRobot__sa.PushBack({ 160, 160, 40, 40 });
	GRobot__sa.PushBack({ 200, 160, 40, 40 });
	GRobot__sa.PushBack({ 240, 160, 40, 40 });
	GRobot__sa.PushBack({ 280, 160, 40, 40 });
	GRobot__sa.loop = true;
	GRobot__sa.speed = 0.1f;

	GRobot__sd.PushBack({ 0, 160, 40, 40 });
	GRobot__sd.PushBack({ 40, 160, 40, 40 });
	GRobot__sd.PushBack({ 80, 160, 40, 40 });
	GRobot__sd.PushBack({ 160, 160, 40, 40 });
	GRobot__sd.loop = true;
	GRobot__sd.speed = 0.1f;

	GRobot__d.PushBack({ 0, 120, 40, 40 });
	GRobot__d.PushBack({ 40, 120, 40, 40 });
	GRobot__d.PushBack({ 120, 120, 40, 40 });
	GRobot__d.PushBack({ 160, 120, 40, 40 });
	GRobot__d.loop = true;
	GRobot__d.speed = 0.1f;


	animation = &GRobot__180;

	collider = App->collision->AddCollider({ 0, 0, 27, 47 }, COLLIDER_TYPE::COLLIDER_GREY_ROBOT, (Module*)App->enemies);

	original_y = y;
	original_x = x;
}

void Enemy_GreyRobot::Move()
{
	bool left = false;
	float angle = 0;

	if ((original_y >= (App->render->camera.y / 2) - RANGE) && (original_y <= (App->render->camera.y / 2) + 340 - RANGE)){
		//left or right of the turret
		if (App->player->position.x >= original_x){
			left = false;
		}
		else{
			left = true;
		}

		//angle
		//angle = (float)acos(((App->player->position.x * 0) + (App->player->position.y * 1)) / ((sqrt((pow((double)App->player->position.x, 2)) + (pow((double)App->player->position.y, 2))))*(sqrt((pow(0.0, 2.0)) + (pow(1.0, 2.0)))))) * ANGLE_CONVERT;

		//angle = ((float)acos(((App->player->position.x * 0) + (App->player->position.y * 1)) / (sqrt((double)((App->player->position.x)*(App->player->position.x) + (App->player->position.y)*(App->player->position.y)))*sqrt((double)(0 * 0 + 1 * 1))))) * ANGLE_CONVERT;

		angle = ((float)acos((((App->player->position.x - original_x) * 0) + ((App->player->position.y - original_y) * 1)) / (sqrt((double)((App->player->position.x - original_x)*(App->player->position.x - original_x) + (App->player->position.y - original_y)*(App->player->position.y - original_y)))*sqrt((double)(0 * 0 + 1 * 1))))) * ANGLE_CONVERT;

		//LOG("Angle %.2f", angle);

		//Right
		if ((angle <= 11.25) && (angle >= 0) && (left == false)){
			animation = &GRobot__180;
		}
		else if ((angle <= 33.75) && (angle >= 11.25) && (left == false)){
			animation = &GRobot__157_5;
		}
		else if ((angle <= 56.25) && (angle >= 33.75) && (left == false)){
			animation = &GRobot__135;
		}
		else if ((angle <= 78.75) && (angle >= 56.25) && (left == false)){
			animation = &GRobot__112_5;
		}
		else if ((angle <= 101.25) && (angle >= 78.75) && (left == false)){
			animation = &GRobot__90;
		}
		else if ((angle <= 123.75) && (angle >= 101.25) && (left == false)){
			animation = &GRobot__67_5;
		}
		else if ((angle <= 146.25) && (angle >= 123.75) && (left == false)){
			animation = &GRobot__45;
		}
		else if ((angle <= 168.75) && (angle >= 146.25) && (left == false)){
			animation = &GRobot__22_5;
		}
		else if ((angle <= 180) && (angle >= 168.75) && (left == false)){
			animation = &GRobot__0;
		}

		//Left
		else if ((angle <= 11.25) && (angle >= 0) && (left == true)){
			animation = &GRobot__180;
		}
		else if ((angle <= 33.75) && (angle >= 11.25) && (left == true)){
			animation = &GRobot__202_5;
		}
		else if ((angle <= 56.25) && (angle >= 33.75) && (left == true)){
			animation = &GRobot__225;
		}
		else if ((angle <= 78.75) && (angle >= 56.25) && (left == true)){
			animation = &GRobot__247_5;
		}
		else if ((angle <= 101.25) && (angle >= 78.75) && (left == true)){
			animation = &GRobot__270;
		}
		else if ((angle <= 123.75) && (angle >= 101.25) && (left == true)){
			animation = &GRobot__292_5;
		}
		else if ((angle <= 146.25) && (angle >= 123.75) && (left == true)){
			animation = &GRobot__315;
		}
		else if ((angle <= 168.75) && (angle >= 146.25) && (left == true)){
			animation = &GRobot__337_5;
		}
		else if ((angle <= 180) && (angle >= 168.75) && (left == true)){
			animation = &GRobot__0;
		}
	}
	position.y = original_y;
	position.x = original_x;
}

void Enemy_GreyRobot::Shoot()
{
	unsigned int currentTime = 0;
	bool left = false;
	float angle = 0;
	int i = 0;

	currentTime = SDL_GetTicks();

	if ((original_y >= (App->render->camera.y / 2) - RANGE) && (original_y <= (App->render->camera.y / 2) + 340 - RANGE)){

		if (App->player->position.x >= original_x){
			left = false;
		}
		else{
			left = true;
		}

		angle = ((float)acos((((App->player->position.x + 14 - original_x) * 0) + ((App->player->position.y + 16 - original_y) * 1)) / (sqrt((double)((App->player->position.x + 14 - original_x)*(App->player->position.x + 14 - original_x) + (App->player->position.y + 16 - original_y)*(App->player->position.y + 16 - original_y)))*sqrt((double)(0 * 0 + 1 * 1))))) * ANGLE_CONVERT;
		//LOG("Angle %.2f", angle);

		if (currentTime > (lastTime + ENEMYSHOOTDELAY)) {
			if (left == true){
				if ((angle < 90) && (angle >= 0)){
					App->particles->enemyshoot.speed.x = -ENEMY_SHOOT_SPEED * sin(angle * ANGLE_CONVERT_REVERSE);
					App->particles->enemyshoot.speed.y = ENEMY_SHOOT_SPEED * cos(angle * ANGLE_CONVERT_REVERSE);
				}
				else{
					App->particles->enemyshoot.speed.x = -ENEMY_SHOOT_SPEED * sin(angle * ANGLE_CONVERT_REVERSE);
					App->particles->enemyshoot.speed.y = ENEMY_SHOOT_SPEED * cos(angle * ANGLE_CONVERT_REVERSE);
				}
			}
			else{
				if ((angle < 90) && (angle >= 0)){
					App->particles->enemyshoot.speed.x = ENEMY_SHOOT_SPEED * sin(angle * ANGLE_CONVERT_REVERSE);
					App->particles->enemyshoot.speed.y = ENEMY_SHOOT_SPEED * cos(angle * ANGLE_CONVERT_REVERSE);
				}
				else{
					App->particles->enemyshoot.speed.x = ENEMY_SHOOT_SPEED * sin(angle * ANGLE_CONVERT_REVERSE);
					App->particles->enemyshoot.speed.y = ENEMY_SHOOT_SPEED * cos(angle * ANGLE_CONVERT_REVERSE);
				}
			}

			if ((angle <= 11.25) && (angle >= 0) && (left == false)){
				App->particles->AddParticle(App->particles->enemyshoot, original_x + 8, original_y + 20, COLLIDER_ENEMY_SHOT);
			}
			else if ((angle <= 33.75) && (angle >= 11.25) && (left == false)){
				App->particles->AddParticle(App->particles->enemyshoot, original_x + 13, original_y + 17, COLLIDER_ENEMY_SHOT);
			}
			else if ((angle <= 56.25) && (angle >= 33.75) && (left == false)){
				App->particles->AddParticle(App->particles->enemyshoot, original_x + 17, original_y + 17, COLLIDER_ENEMY_SHOT);
			}
			else if ((angle <= 78.75) && (angle >= 56.25) && (left == false)){
				App->particles->AddParticle(App->particles->enemyshoot, original_x + 20, original_y + 14, COLLIDER_ENEMY_SHOT);
			}
			else if ((angle <= 101.25) && (angle >= 78.75) && (left == false)){
				App->particles->AddParticle(App->particles->enemyshoot, original_x + 22, original_y + 10, COLLIDER_ENEMY_SHOT);
			}
			else if ((angle <= 123.75) && (angle >= 101.25) && (left == false)){
				App->particles->AddParticle(App->particles->enemyshoot, original_x + 20, original_y + 3, COLLIDER_ENEMY_SHOT);
			}
			else if ((angle <= 146.25) && (angle >= 123.75) && (left == false)){
				App->particles->AddParticle(App->particles->enemyshoot, original_x + 18, original_y, COLLIDER_ENEMY_SHOT);
			}
			else if ((angle <= 168.75) && (angle >= 146.25) && (left == false)){
				App->particles->AddParticle(App->particles->enemyshoot, original_x + 14, original_y - 3, COLLIDER_ENEMY_SHOT);
			}
			else if ((angle <= 180) && (angle >= 168.75) && (left == false)){
				App->particles->AddParticle(App->particles->enemyshoot, original_x + 8, original_y - 4, COLLIDER_ENEMY_SHOT);
			}

			//Left
			else if ((angle <= 11.25) && (angle >= 0) && (left == true)){
				App->particles->AddParticle(App->particles->enemyshoot, original_x + 8, original_y + 20, COLLIDER_ENEMY_SHOT);
			}
			else if ((angle <= 33.75) && (angle >= 11.25) && (left == true)){
				App->particles->AddParticle(App->particles->enemyshoot, original_x + 3, original_y + 19, COLLIDER_ENEMY_SHOT);
			}
			else if ((angle <= 56.25) && (angle >= 33.75) && (left == true)){
				App->particles->AddParticle(App->particles->enemyshoot, original_x - 1, original_y + 13, COLLIDER_ENEMY_SHOT);
			}
			else if ((angle <= 78.75) && (angle >= 56.25) && (left == true)){
				App->particles->AddParticle(App->particles->enemyshoot, original_x - 3, original_y + 9, COLLIDER_ENEMY_SHOT);
			}
			else if ((angle <= 101.25) && (angle >= 78.75) && (left == true)){
				App->particles->AddParticle(App->particles->enemyshoot, original_x - 4, original_y + 8, COLLIDER_ENEMY_SHOT);
			}
			else if ((angle <= 123.75) && (angle >= 101.25) && (left == true)){
				App->particles->AddParticle(App->particles->enemyshoot, original_x - 3, original_y + 3, COLLIDER_ENEMY_SHOT);
			}
			else if ((angle <= 146.25) && (angle >= 123.75) && (left == true)){
				App->particles->AddParticle(App->particles->enemyshoot, original_x - 1, original_y + 1, COLLIDER_ENEMY_SHOT);
			}
			else if ((angle <= 168.75) && (angle >= 146.25) && (left == true)){
				App->particles->AddParticle(App->particles->enemyshoot, original_x + 4, original_y, COLLIDER_ENEMY_SHOT);
			}
			else if ((angle <= 180) && (angle >= 168.75) && (left == true)){
				App->particles->AddParticle(App->particles->enemyshoot, original_x + 8, original_y - 4, COLLIDER_ENEMY_SHOT);
			}
			lastTime = currentTime;
		}
	}
}
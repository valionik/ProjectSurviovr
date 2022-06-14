#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <math.h>
#include <vector>

#include <cstdlib>
#include <time.h>

#include <functional>

#include <fstream>

#include "RenderWindow.h"
#include "Utils.h"
#include "Button.h"
#include "Methods.h"
#include "Placeholder.h"
#include "Text.h"
#include "IslandButton.h"

using namespace Methods;
using namespace std;

//dimentions of window
#define WIDTH 1280
#define HEIGHT 720
//start X position of the bars
#define STARTOFBARS 10
const static string FONTPATH = "res/arcedeclassic.ttf";

//define some functions
void decreaseHealthValue(float& v, int shelterState);
void decreaseBarValue(float& v);


int main(int argc, char* argv[]) {

	//check for errors

	if (SDL_Init(SDL_INIT_VIDEO) > 0) cout << "SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << endl;

	if (!(IMG_Init(IMG_INIT_PNG))) cout << "IMG_Init has failed. Error: " << IMG_GetError() << endl;

	if (TTF_Init() == -1) cout << "TTF_Init has failed Error: " << TTF_GetError() << endl;

	RenderWindow window("SURVIVOR GAME v1.0", WIDTH, HEIGHT);

	//load textures

	SDL_Texture* island1Texture = window.loadTexture("res/island1.png");

	SDL_Texture* island2Texture = window.loadTexture("res/island2.png");

	SDL_Texture* island3Texture = window.loadTexture("res/island3.png");

	SDL_Texture* heartTexture = window.loadTexture("res/heart.png");

	SDL_Texture* meatTexture = window.loadTexture("res/meat.png");

	SDL_Texture* waterTexture = window.loadTexture("res/water.png");

	SDL_Texture* huntTexture = window.loadTexture("res/hunt.png");

	SDL_Texture* searchForWaterTexture = window.loadTexture("res/search_for_water.png");

	SDL_Texture* upgradeTexture = window.loadTexture("res/upgrade.png");

	SDL_Texture* safeAnimalTexture = window.loadTexture("res/safe_animal.png");

	SDL_Texture* dangerousAnimalTexture = window.loadTexture("res/dangerous_animal.png");

	SDL_Texture* upgradeShelterTexture = window.loadTexture("res/upgrade_shelter.png");

	SDL_Texture* makeWeaponTexture = window.loadTexture("res/make_a_weapon.png");

	SDL_Texture* expandInventoryTexture = window.loadTexture("res/expand_inventory.png");

	SDL_Texture* placeholderTexture = window.loadTexture("res/placeholder.png");

	SDL_Texture* eggsTexture = window.loadTexture("res/eggs.png");

	SDL_Texture* beefTexture = window.loadTexture("res/beef.png");

	SDL_Texture* weaponTexture = window.loadTexture("res/weapon.png");

	SDL_Texture* waterBottleTexture = window.loadTexture("res/water_bottle.png");

	SDL_Texture* island1ButtonTexture = window.loadTexture("res/island_1.png");

	SDL_Texture* island2ButtonTexture = window.loadTexture("res/island_2.png");

	SDL_Texture* island3ButtonTexture = window.loadTexture("res/island_3.png");

	SDL_Texture* burqTexture = window.loadTexture("res/burq.png");

	SDL_Texture* youDiedTexture = window.loadTexture("res/you_died.png");

	SDL_Texture* youSurvivedTexture = window.loadTexture("res/you_survived.png");

	SDL_Texture* continueButtonTexture = window.loadTexture("res/continue.png");

	//Create flags

	int daysSurvived = 0;
	int shelterIndex = 0;
	int selectedIsland = 1;
	int huntedAnimalsForTheDay = 0;
	int daysStayedOnIsland = 0;

	bool isDead = false;
	bool gameRunning = true;
	bool inventoryTextTrigger = false;
	bool hurtTextTrigger = false;
	bool outOfResourcesTextTrigger = false;

	//State stands for what button is pressed, therefore what to show on the screen
	//We will switch the state and change it in different events
	//0 means nothing is pressed, new day starts
	//1 means hunt is selected
	//2 means upgrade is selected
	//3 means storm
	//4 means island out of resources
	//5 means survivor died
	//6 means surviver survived

	int state = 0;

	////....................INITIALIZE TEXTURES..............

	//health bar

	vector<Entity> health;
	float healthValue = 10;
	float healthPosX = STARTOFBARS;

	float StartPosY = 5;

	Entity heart(healthPosX, StartPosY, heartTexture);

	for (int i = 0;i < floor(healthValue);i++) {
		heart.setX(healthPosX);
		health.push_back(heart);
		healthPosX += heart.getCurrentFrame().w + 1;
	}

	//hunger bar

	vector<Entity> hunger;
	float hungerValue = 10;
	float hungerPosX = STARTOFBARS;

	Entity meat(hungerPosX, StartPosY, meatTexture);
	StartPosY += meat.getCurrentFrame().h + 1;
	meat.setY(StartPosY);

	for (int i = 0;i < floor(hungerValue);i++)
	{
		meat.setX(hungerPosX);
		hunger.push_back(meat);
		hungerPosX += meat.getCurrentFrame().w + 1;
	}

	//thirst bar

	vector<Entity> thirst;
	float thirstValue = 10;
	float thirstPosX = STARTOFBARS;

	Entity water(thirstPosX, StartPosY, waterTexture);
	StartPosY += water.getCurrentFrame().h + 1;
	water.setY(StartPosY);

	for (int i = 0;i < floor(thirstValue);i++)
	{
		water.setX(thirstPosX);
		thirst.push_back(water);
		thirstPosX += water.getCurrentFrame().w + 1;
	}

	//Initialize hardcoded buttons to stay in place

	Button huntButton(WIDTH / 2 - 200, 128, huntTexture);
	Button waterButton(WIDTH / 2 - 200, 232, searchForWaterTexture);
	Button upgradeButton(WIDTH / 2 - 200, 336, upgradeTexture);

	Button safeAnimalButton(WIDTH / 3 - 210, 232, safeAnimalTexture);
	Button dangerousAnimalButton(WIDTH / 3 + 210, 232, dangerousAnimalTexture);

	Button upgradeShelterButton(WIDTH / 3 - 210, 128, upgradeShelterTexture);
	Button makeWeaponButton(WIDTH / 3 + 210, 128, makeWeaponTexture);
	Button expandInventoryButton(WIDTH / 2 - 200, 232, expandInventoryTexture);

	Button continueButton(WIDTH / 2 - 200, 450, continueButtonTexture);

	IslandButton island1Button(WIDTH - 210, 10, island1ButtonTexture);
	IslandButton island2Button(WIDTH - 210, 64, island2ButtonTexture);
	IslandButton island3Button(WIDTH - 210, 118, island3ButtonTexture);

	//Initialize inventory

	vector<Placeholder> inventory;
	Placeholder placeholder(WIDTH / 3 - 64, HEIGHT - 144, placeholderTexture);
	inventory.push_back(placeholder);

	//Initialize items

	Item waterBottle(placeholder.getX() + 36, placeholder.getY() + 36, waterBottleTexture);
	Item egg(placeholder.getX() + placeholder.getCurrentFrame().w / 2 + 36, placeholder.getY() + 36, eggsTexture);
	Item beef(placeholder.getX() + placeholder.getCurrentFrame().w + 36, placeholder.getY() + 36, beefTexture);
	Item weapon(placeholder.getX() + placeholder.getCurrentFrame().w * 1.5 + 36, placeholder.getY() + 36, weaponTexture);

	//Initialize text

	string survived = "DAYS SURVIVED:";
	string shelterStatusMessage = "SHELTER STATUS : ";
	Text shelterText(window.getRenderer(), FONTPATH, 16, shelterStatusMessage, { 0, 0, 0, 0 });

	vector<string> shelterStatus =
	{
		"NONE",
		"BASIC HUT : 20% REDUCED DAMAGE",
		"ADVANCED HUT : 25% REDUCED DAMAGE",
		"CHAD HOUSE : 30% REDUCED DAMAGE"
	};

	Text notEnoughInventoryText(window.getRenderer(), FONTPATH, 16, "Not enough inventory space...", { 255, 255, 255, 255 });
	Text youGotHurtText(window.getRenderer(), FONTPATH, 16, "You got hurt...", { 255, 255, 255, 255 });
	Text outOfResourcesText(window.getRenderer(), FONTPATH, 16, "Island is out of resources...", { 255, 255, 255, 255 });

	//RNG

	srand(time(0));

	//Open file logger

	ofstream log("log/actions.txt");
	if (!log) cout << "Can't find the file";


	///...............INITIALIZE STORM FUNCTION IN ORDER TO NOT REPEAT IT 100 TIMES.................

	function<void()> storm = [&]() {

		state = 3;
		daysSurvived++;
		daysStayedOnIsland+=4;
		healthValue -= 2;
		hungerValue -= 2;
		shelterIndex = 0;

		// If you want to make it harder
		//for (int i = inventory.size(); i > 1; i--) {
		//	inventory.pop_back();
		//}

		waterBottle.setCount(0);
		egg.setCount(0);
		beef.setCount(0);
		weapon.setCount(0);
		thirstValue = 10;

		log << "Day : " << daysSurvived << " a storm has occured" << "\n";
		log << "Health : " << healthValue << " Hunger : " << hungerValue << " Thirst : " << thirstValue << "\n";
	};

	//Event handler
	SDL_Event event;

	//Variables to take care for the FPS
	const float timeStep = 0.01f;
	float accumolator = 0.0f;
	float currentTime = utils::hireTimeInSeconds();

	//game loop
	while (gameRunning)
	{
		//fps handlers
		int startTicks = SDL_GetTicks();

		float newTime = utils::hireTimeInSeconds();
		float frameTime = newTime - currentTime;

		currentTime = newTime;

		accumolator += frameTime;

		while (accumolator >= timeStep)
		{
			//get our and events 
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT) gameRunning = false;
				if (huntButton.isPressed(&event) && state == 0)
				{
					hurtTextTrigger = false;
					if (inventory.size() == 1)
					{
						inventoryTextTrigger = true;
						state = 0;
					}
					else {
						state = 1;
						huntedAnimalsForTheDay = 0;
					}

					if ((daysStayedOnIsland >= 10 && daysStayedOnIsland < 14)||(daysStayedOnIsland >= 24 && daysStayedOnIsland < 28))
					{
						outOfResourcesTextTrigger = true;
						state = 0;
					}
				}
				if (waterButton.isPressed(&event) && state == 0)
				{
					outOfResourcesTextTrigger = false;
					hurtTextTrigger = false;
					inventoryTextTrigger = false;
					//give water
					if (rand() % 10 + 1 == 1)
					{
						storm();
					}
					else
					{
						waterBottle.setCount(waterBottle.getCount() + 1);
						//decrease other bars
						hungerValue--;
						decreaseHealthValue(healthValue, shelterIndex);
						daysSurvived++;
						daysStayedOnIsland++;
						log << "Day : " << daysSurvived << " Player searched for water" << "\n";
						log << "Health : " << healthValue << " Hunger : " << hungerValue << " Thirst : " << thirstValue << "\n";
					}
				}
				if (upgradeButton.isPressed(&event) && state == 0)
				{
					outOfResourcesTextTrigger = false;
					hurtTextTrigger = false;
					inventoryTextTrigger = false;
					state = 2;
				}


				if (safeAnimalButton.isPressed(&event) && state == 1)
				{
					inventoryTextTrigger = false;
					//give eggs
					egg.setCount(egg.getCount() + 1);
					//chance to get hurt
					switch (selectedIsland)
					{
					case 1:
						if (weapon.getCount() >= 1)
						{
							if (rand() % 30 + 1 <= 1)
							{
								hurtTextTrigger = true;
								decreaseHealthValue(healthValue, shelterIndex);
							}
							weapon.setCount(weapon.getCount() - 1);
						}
						else {
							if (rand() % 10 + 1 <= 1)
							{
								hurtTextTrigger = true;
								decreaseHealthValue(healthValue, shelterIndex);
							}
						}
						break;
					case 2:
						if (weapon.getCount() >= 1)
						{
							if (rand() % 30 + 1 <= 2)
							{
								hurtTextTrigger = true;
								decreaseHealthValue(healthValue, shelterIndex);
							}
							weapon.setCount(weapon.getCount() - 1);
						}
						else {
							if (rand() % 10 + 1 <= 2)
							{
								hurtTextTrigger = true;
								decreaseHealthValue(healthValue, shelterIndex);
							}
						}
						break;
					case 3:
						if (weapon.getCount() >= 1)
						{
							if (rand() % 10 + 1 <= 1)
							{
								hurtTextTrigger = true;
								decreaseHealthValue(healthValue, shelterIndex);
							}
							weapon.setCount(weapon.getCount() - 1);
						}
						else {
							if (rand() % 10 + 1 <= 3)
							{
								hurtTextTrigger = true;
								decreaseHealthValue(healthValue, shelterIndex);
							}
						}
						break;
					}
					huntedAnimalsForTheDay++;
					if (huntedAnimalsForTheDay == 2)
					{
						if (rand() % 10 + 1 == 1)
						{
							storm();
						}
						else
						{
							state = 0;
							daysSurvived++;
							daysStayedOnIsland++;
							thirstValue--;

							log << "Day : " << daysSurvived << " Player hunted animals" << "\n";
							log << "Health : " << healthValue << " Hunger : " << hungerValue << " Thirst : " << thirstValue << "\n";
						}
					}
				}
				if (dangerousAnimalButton.isPressed(&event) && state == 1)
				{
					if (inventory.size() <= 2)
					{

						state = 1;
						inventoryTextTrigger = true;
					}
					else
					{

						//give beef
						beef.setCount(beef.getCount() + 1);
						//chance to get hurt
						switch (selectedIsland)
						{
						case 1:
							if (weapon.getCount() >= 1)
							{
								if (rand() % 30 + 1 <= 5)
								{
									hurtTextTrigger = true;
									decreaseHealthValue(healthValue, shelterIndex);
								}
								weapon.setCount(weapon.getCount() - 1);
							}
							else {
								if (rand() % 10 + 1 <= 5)
								{
									hurtTextTrigger = true;
									decreaseHealthValue(healthValue, shelterIndex);
								}
							}
							break;
						case 2:
							if (weapon.getCount() >= 1)
							{
								if (rand() % 30 + 1 <= 6)
								{
									hurtTextTrigger = true;
									decreaseHealthValue(healthValue, shelterIndex);
								}
								weapon.setCount(weapon.getCount() - 1);
							}
							else {
								if (rand() % 10 + 1 <= 6)
								{
									hurtTextTrigger = true;
									decreaseHealthValue(healthValue, shelterIndex);
								}
							}
							break;
						case 3:
							if (weapon.getCount() >= 1)
							{
								if (rand() % 30 + 1 <= 7)
								{
									hurtTextTrigger = true;
									decreaseHealthValue(healthValue, shelterIndex);
								}
								weapon.setCount(weapon.getCount() - 1);
							}
							else {
								if (rand() % 10 + 1 <= 7)
								{
									hurtTextTrigger = true;
									decreaseHealthValue(healthValue, shelterIndex);
								}
							}
							break;
						}
						huntedAnimalsForTheDay++;
						if (huntedAnimalsForTheDay == 2)
						{
							if (rand() % 10 + 1 == 1)
							{
								storm();
							}
							else
							{
								state = 0;
								thirstValue--;
								daysStayedOnIsland++;
								daysSurvived++;
								log << "Day : " << daysSurvived << " Player hunted animals" << "\n";
								log << "Health : " << healthValue << " Hunger : " << hungerValue << " Thirst : " << thirstValue << "\n";
							}
						}
					}
				}


				if (upgradeShelterButton.isPressed(&event) && state == 2)
				{
					inventoryTextTrigger = false;
					if (rand() % 10 + 1 == 1)
					{
						storm();
					}
					else
					{
						if (shelterIndex < 3)	shelterIndex++;
						state = 0;
						decreaseBarValue(hungerValue);
						decreaseBarValue(thirstValue);
						daysSurvived++;
						daysStayedOnIsland++;
						log << "Day : " << daysSurvived << " Player upgraded shelter" << "\n";
						log << "Health : " << healthValue << " Hunger : " << hungerValue << " Thirst : " << thirstValue << "\n";
					}
				}
				if (makeWeaponButton.isPressed(&event) && state == 2)
				{
					if (inventory.size() >= 4)
					{
						if (rand() % 10 + 1 == 1)
						{
							storm();
						}
						else {
							weapon.setCount(weapon.getCount() + 1);
							state = 0;
							decreaseBarValue(hungerValue);
							decreaseBarValue(thirstValue);
							daysSurvived++;
							daysStayedOnIsland++;
							log << "Day : " << daysSurvived << " Player made a weapon" << "\n";
							log << "Health : " << healthValue << " Hunger : " << hungerValue << " Thirst : " << thirstValue << "\n";
						}
					}
					else {
						inventoryTextTrigger = true;
					}

				}
				if (expandInventoryButton.isPressed(&event) && state == 2)
				{
					outOfResourcesTextTrigger = false;
					inventoryTextTrigger = false;
					if (rand() % 10 + 1 == 1)
					{
						storm();
					}
					else
					{
						if (inventory.size() < 4)	increaseInventory(inventory, placeholder);
						state = 0;
						decreaseBarValue(hungerValue);
						decreaseBarValue(thirstValue);
						daysSurvived++;
						daysStayedOnIsland++;

						log << "Day : " << daysSurvived << " Player expanded inventory" << "\n";
						log << "Health : " << healthValue << " Hunger : " << hungerValue << " Thirst : " << thirstValue << "\n";
					}
				}

				if (continueButton.isPressed(&event))
				{
					state = 0;

					//Uncomment if you want to decrease inventory capacity after storm
					//placeholder.setX(WIDTH / 3 - 64);
					//placeholder.setY(HEIGHT - 144);
				}

				if (egg.isPressed(&event))
				{
					//fill some hunger bar
					if (egg.getCount() > 0)
					{
						egg.setCount(egg.getCount() - 1);

						hungerValue = hungerValue + (10 - hungerValue) / (rand() % 5 + 1);

					}
				}
				if (waterBottle.isPressed(&event))
				{
					//fill some thirst bar
					if (waterBottle.getCount() > 0)
					{
						waterBottle.setCount(waterBottle.getCount() - 1);
						thirstValue = thirstValue + (10 - thirstValue) / (rand() % 5 + 1);
					}
				}
				if (beef.isPressed(&event))
				{
					//fill more hunger bar
					if (beef.getCount() > 0)
					{
						beef.setCount(beef.getCount() - 1);
						hungerValue = hungerValue + (10 - hungerValue) / (rand() % 3 + 1);
					}
				}


				if (island1Button.isPressed(&event))
				{
					if (selectedIsland != 1) 
					{
						outOfResourcesTextTrigger = false;
						selectedIsland = 1;

						healthValue--;
						hungerValue--;
						thirstValue--;

						daysStayedOnIsland = 0;

						log << "Day : " << daysSurvived << " Player moved to Island 1" << "\n";
						log << "Health : " << healthValue << " Hunger : " << hungerValue << " Thirst : " << thirstValue << "\n";
					}
				}
				if (island2Button.isPressed(&event))
				{
					if (selectedIsland != 2) 
					{
						outOfResourcesTextTrigger = false;
						selectedIsland = 2;

						healthValue--;
						hungerValue--;
						thirstValue--;

						daysStayedOnIsland = 0;
						log << "Day : " << daysSurvived << " Player moved to Island 2" << "\n";
						log << "Health : " << healthValue << " Hunger : " << hungerValue << " Thirst : " << thirstValue << "\n";
					}
				}
				if (island3Button.isPressed(&event))
				{
					if (selectedIsland != 3)
					{
						outOfResourcesTextTrigger = false;
						selectedIsland = 3;

						healthValue--;
						hungerValue--;
						thirstValue--;

						daysStayedOnIsland = 0;

						log << "Day : " << daysSurvived << " Player moved to island 3" << "\n";
						log << "Health : " << healthValue << " Hunger : " << hungerValue << " Thirst : " << thirstValue << "\n";
					}
				}
			}

			accumolator -= timeStep;

		}

		const float alpha = accumolator / timeStep;


		if (daysSurvived >= 30)
		{
			state = 6;
		}

		if (healthValue <= 0 || hungerValue <= 0 || thirstValue <= 0)
		{
			state = 5;
		}

		//render
		window.clear();



		if (state <= 2 || state == 4)
		{
			if (selectedIsland == 1)
			{
				window.renderTexture(island1Texture);
			}
			if (selectedIsland == 2)
			{
				window.renderTexture(island2Texture);
			}
			if (selectedIsland == 3)
			{
				window.renderTexture(island3Texture);
			}
		}
		if (state == 3)
		{
			window.renderTexture(burqTexture);
		}
		if (state == 5)
		{
			window.renderTexture(youDiedTexture);
		}
		if (state == 6)
		{
			window.renderTexture(youSurvivedTexture);
		}

		//.....................CHECK THE VALUES OF THE BARS.....................


		if (healthValue > 0 && hungerValue > 0 && thirstValue > 0)
		{
			if (healthValue < health.size())
			{
				for (int i = floor(healthValue);i < health.size();i++) {
					decreaseBar(health, heart);
				}
			}
			else if (healthValue > health.size())
			{
				for (int i = health.size();i < floor(healthValue);i++)
				{
					increaseBar(health, heart);
				}
			}


			if (hungerValue < hunger.size())
			{
				for (int i = floor(hungerValue);i < hunger.size();i++) {
					decreaseBar(hunger, meat);
				}
			}
			else if (hungerValue > hunger.size())
			{
				for (int i = hunger.size();i < floor(hungerValue);i++)
				{
					increaseBar(hunger, meat);
				}
			}

			if (thirstValue < thirst.size())
			{
				for (int i = floor(thirstValue);i < thirst.size();i++) {
					decreaseBar(thirst, water);
				}
			}
			else if (thirstValue > thirst.size())
			{
				for (int i = thirst.size();i < floor(thirstValue);i++)
				{
					increaseBar(thirst, water);
				}
			}
		}
		//.........................................................


		for (Entity& h : health) {
			window.renderEntity(h);
		}
		for (Entity& m : hunger) {
			window.renderEntity(m);
		}
		for (Entity& w : thirst) {
			window.renderEntity(w);
		}

		if (healthValue > 0 && hungerValue > 0 && thirstValue > 0 && state != 6)
		{
			window.renderIslandButton(island1Button);
			window.renderIslandButton(island2Button);
			window.renderIslandButton(island3Button);
		}
		//................RENDER TEXT...........................

		survived.resize(14);
		survived += to_string(daysSurvived);
		Text daysSurvivedText(window.getRenderer(), FONTPATH, 28, survived, { 0, 0, 0, 0 });
		if (state != 3)
		{
			daysSurvivedText.display(WIDTH / 3 + 20, 20, window.getRenderer());
		}
		Text shelterStatusText(window.getRenderer(), FONTPATH, 12, shelterStatus[shelterIndex], { 0, 0, 0, 0 });

		if (healthValue > 0 && hungerValue > 0 && thirstValue > 0 && state != 3)
		{
			shelterStatusText.display(WIDTH / 3 + 20, 80, window.getRenderer());

			shelterText.display(WIDTH / 3 + 20, 60, window.getRenderer());

			if (inventoryTextTrigger) notEnoughInventoryText.display(WIDTH / 3, 480, window.getRenderer());
			if (hurtTextTrigger) youGotHurtText.display(WIDTH / 3 + 100, 480, window.getRenderer());
			if (outOfResourcesTextTrigger) outOfResourcesText.display(WIDTH / 3, 480, window.getRenderer());
		}
		//.............................................

		switch (state)
		{
		case 0:
			window.renderButton(huntButton);
			window.renderButton(waterButton);
			window.renderButton(upgradeButton);
			break;
		case 1:
			window.renderButton(safeAnimalButton);
			window.renderButton(dangerousAnimalButton);
			break;
		case 2:
			window.renderButton(upgradeShelterButton);
			window.renderButton(makeWeaponButton);
			window.renderButton(expandInventoryButton);
			break;
		case 3:
			window.renderButton(continueButton);
		}

		if (healthValue > 0 && hungerValue > 0 && thirstValue > 0 && state != 3)
		{
			for (Placeholder& p : inventory) {
				window.renderPlaceholder(p);
			}
		}

		Text waterBottleCount(window.getRenderer(), FONTPATH, 15, to_string(waterBottle.getCount()), { 255, 255, 255, 255 });
		Text eggCount(window.getRenderer(), FONTPATH, 15, to_string(egg.getCount()), { 255, 255, 255, 255 });
		Text beefCount(window.getRenderer(), FONTPATH, 15, to_string(beef.getCount()), { 255, 255, 255, 255 });
		Text weaponCount(window.getRenderer(), FONTPATH, 15, to_string(weapon.getCount()), { 255, 255, 255, 255 });

		if (healthValue > 0 && hungerValue > 0 && thirstValue > 0)
		{
			if (inventory.size() >= 1)
			{
				window.renderItem(waterBottle);
				waterBottleCount.display(waterBottle.getX() + 70, waterBottle.getY() + 70, window.getRenderer());
			}
			if (inventory.size() >= 2)
			{
				window.renderItem(egg);
				eggCount.display(egg.getX() + 70, egg.getY() + 70, window.getRenderer());
			}
			if (inventory.size() >= 3)
			{
				window.renderItem(beef);
				beefCount.display(beef.getX() + 70, beef.getY() + 70, window.getRenderer());
			}
			if (inventory.size() >= 4)
			{
				window.renderItem(weapon);
				weaponCount.display(weapon.getX() + 70, weapon.getY() + 70, window.getRenderer());
			}
		}


		window.display();

		int frameTicks = SDL_GetTicks() - startTicks;

		if (frameTicks < 1000 / window.getRefreshRate())
			SDL_Delay(1000 / window.getRefreshRate() - frameTicks);

		//Clean textures for memory leaks
		daysSurvivedText.cleanUp();
		shelterStatusText.cleanUp();
		waterBottleCount.cleanUp();
		eggCount.cleanUp();
		beefCount.cleanUp();
		weaponCount.cleanUp();

	}
	if (state == 5) {
		log << "Day : " << daysSurvived << " Player died" << "\n";
		log << "Health : " << healthValue << " Hunger : " << hungerValue << " Thirst : " << thirstValue << "\n";
	}
	if (state == 6) {
		log << "Day : " << daysSurvived << " Player is rescued" << "\n";
		log << "Health : " << healthValue << " Hunger : " << hungerValue << " Thirst : " << thirstValue << "\n";
	}

	window.cleanUp();
	TTF_Quit();
	SDL_Quit();

	return 0;
}

void decreaseHealthValue(float& v, int shelterState) {
	srand(time(0));
	switch (shelterState)
	{
	case 0:
		v = v - (10 - v) / (rand() % 5 + 1);
		break;
	case 1:
		v = v - 0.8 * (10 - v) / (rand() % 5 + 1);
		break;
	case 2:
		v = v - 0.75 * (10 - v) / (rand() % 5 + 1);
		break;
	case 3:
		v = v - 0.7 * (10 - v) / (rand() % 5 + 1);
	}
}
void decreaseBarValue(float& v) {
	srand(time(0));
	v = v - (10 - v) / (rand() % 5 + 1);
}
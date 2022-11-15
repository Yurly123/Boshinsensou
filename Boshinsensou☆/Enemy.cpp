#include "Enemy.h"

vector<Enemy> Enemy::EnemyList = vector<Enemy>();
int Enemy::Progression = 0;



void Enemy::LoadEnemy()
{
	ifstream enemyStream("CSV\\Enemy.csv");
	string buffer;

	while (!enemyStream.eof())
	{
		getline(enemyStream, buffer, ',');
		int id = stoi(buffer);

		getline(enemyStream, buffer, ',');
		string name = buffer;

		EnemyList.push_back(Enemy(id, name));

		getline(enemyStream, buffer);
	}

	enemyStream.close();
}

Enemy::Enemy(int id, string name)
{
	this->id = id;
	this->name = name;
}
#include "Enemy.h"

#pragma region 클래스 멤버

#pragma region Enemy
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
#pragma endregion

#pragma endregion

#pragma region 전역 함수

void ShowEnemyInfo(Enemy& enemy)
{
	PrintLine();
	cout << endl;

	cout << "   -" << enemy.name << "-" << endl;

	cout << endl;
	cout << GetEnemyDescription(enemy.id);
	cout << endl;

	cout << endl;
	PrintLine();
	Wait;
}

string GetEnemyDescription(int id)
{
	string description;

	switch (id)
	{
	case 0:	// 히데
		description += "인간의 쓰레기\n";
		description += "음몽계의 최약체\n";
		break;
	default:
		description += "누구?\n";
		break;
	}

	return description;
}

#pragma endregion
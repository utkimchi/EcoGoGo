#include <string>
#include <iostream>
#include <stdlib.h>

class ResourceSystem
{
private:
	std::string nn;
public:
	int n;
};

class ResourceUnits
{
private:
	std::string name;
};

struct location {
	double x, y;
};

class Agent
{
private:
	std::string agentName;
	sf::IntRect bound;
	double maxSpeed;
public:
	int leadership, knowledge, mid, sz;
	std::string mBelief;
	sf::Sprite body, face;
	location loc, move;

	//Constructor
	Agent(std::string n, int l, int k, std::string morals, sf::Texture &bb, int size, sf::IntRect b,double mxs, sf::Texture &p)
	{
		agentName = n;
		leadership = l;
		knowledge = k;
		mBelief = morals;
		mid = size / 2;
		sz = size;
		loc.x = rand() % b.width + b.left;
		loc.y = rand() % b.height + b.top;
		bound = b;
		maxSpeed = mxs;
		move.x = (rand() / (RAND_MAX + maxSpeed));
		move.y = (rand() / (RAND_MAX + maxSpeed));
		body.setTexture(bb);
		body.setTextureRect(sf::IntRect(0,0,size, size));
		body.setPosition(loc.x, loc.y);
		face.setTexture(p);
		face.setTextureRect(sf::IntRect(100, 0, 500, 750));
		face.setPosition(40, 25);
	}

	std::string getName()
	{
		return(agentName);
	}

	void updatePos(location l)
	{
		loc = l;
		body.setPosition(loc.x, loc.y);
	}

	void wander()
	{
		///Generates variable move speed
		if ((!bound.contains(loc.x + sz, loc.y + sz)) || (!bound.contains(loc.x,loc.y)) )
		{
			float xx = (rand() / (RAND_MAX + maxSpeed));
			float yy = (rand() / (RAND_MAX + maxSpeed));

			std::cout << xx << "  " << yy << "\n";

			if (loc.x <= bound.left)
			{
				move.x = xx;
			}

			else if (loc.y <= bound.top)
			{
				move.y = yy;
			}
			else
			{
				move.x = -xx;
				move.y = -yy;
			}
		}
		loc.x = loc.x + move.x;
		loc.y = loc.y + move.y;
		body.setPosition(loc.x, loc.y);
	}

};

class Users
{
private:
	std::string groupName;
public:
	std::vector<Agent> agents;
	sf::RectangleShape area;

	void addUser(Agent &a) {
		agents.push_back(a);
	}
	void printUsers()
	{
		for (auto& x : agents) {
			std::cout << x.getName() << "\n";
		}
	}
	void setArea(sf::Vector2f size, int xp, int yp, sf::Color col)
	{
		area.setSize(size);
		area.setPosition(xp, yp);
		area.setOutlineColor(col);
		area.setOutlineThickness(5);
		area.setFillColor(sf::Color::Black);
	}

	std::vector<sf::VertexArray> connections() {
		std::vector<sf::VertexArray> allLs;
		int connNum = 1; int outsideNum = 1;
		int remainingPeeps = agents.size();
		for (auto& a : agents)
		{
			while (remainingPeeps != connNum)
			{
				sf::VertexArray line(sf::Quads,4);
				Agent nextA = agents[connNum];
				int cx1 = (a.loc.x + a.mid);
				int cy1 = (a.loc.y + a.mid);
				int cx2 = (nextA.loc.x + nextA.mid);
				int cy2 = (nextA.loc.y + nextA.mid);
				line[0].position = sf::Vector2f(cx1,cy1);
				line[1].position = sf::Vector2f(cx1 + 5, cy1 + 5);
				line[2].position = sf::Vector2f(cx2, cy2);
				line[3].position = sf::Vector2f(cx2 +5, cy2 + 5);
				allLs.push_back(line);
				connNum++;
			};
			connNum = outsideNum;
			outsideNum++;
		}

		return allLs;
	}
};

class Connection
{
private:
public:
	std::vector<sf::VertexArray> lines;

	//sf::ConvexShape createLine(sf::Vector2f p1, sf::Vector2f p2)
	
};



class GovernanceSystems
{

};
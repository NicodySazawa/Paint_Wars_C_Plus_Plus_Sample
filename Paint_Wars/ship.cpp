#include "ship.h"
Ship::Ship() :
  _velocity(0), _maxVelocity(1500.f),
  _thrust(0), _maxThrust(1500.f),
  shipPosX(0), shipPosY(0)
{

}
Ship::~Ship()
{
}
float Ship::GetVelocity() 
{
  return _velocity;
}
void Ship::setShipPosX(int newPosX)
{
	shipPosX = newPosX;
}
void Ship::setShipPosY(int newPosY)
{
	shipPosY = newPosY;
}
int Ship::getShipPosX()
{
	return shipPosX;
}
int Ship::getShipPosY()
{
	return shipPosY;
}


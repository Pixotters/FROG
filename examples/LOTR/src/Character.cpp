Character::Character(const std::string& _nane,
		     const unsigned short& _health, 
		     const unsigned short& _resistance, 
		     const unsigned short& _strength, 
		     const unsigned short& _stamina)
  : name(_name), 
    health(_health),
    resistance(_resistance),
    strength(_strength),
    stamina(_stamina)
{
  m_name = n;
  m_health = h;
  m_resistance = r;
  m_attack = a;
  m_stamina = sta;
  m_basename = n;
}

Character::~Character()
{
}

void Character::loadFromFile(const std::string& f)
{
}

std::string Character::getName() const
{ 
  return name; 
}

unsigned short Character::getHealth() const
{ 
  return health; 
}

unsigned short Character::getResistance() const
{ 
  return resistance; 
}

unsigned short Character::getAttack() const
{
  return strength; 
}

unsigned short Character::getStamina() const
{ 
  return stamina; 
}

std::string Character::getBasename() const
{
  return basename;
}

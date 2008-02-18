/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

/*
 *	server/zone/objects/tangible/weapons/Weapon.h generated by Engine3 IDL compiler 0.51
 */

#ifndef WEAPON_H_
#define WEAPON_H_

#include "engine/orb/ObjectRequestBroker.h"

class SceneObject;

class TangibleObject;

class Player;

class Powerup;

#include "../TangibleObject.h"

class Weapon : public TangibleObject {
public:
	Weapon();
	Weapon(ORBObjectServant* obj);
	Weapon(Weapon& ref);

	Weapon* clone();

	virtual ~Weapon();

	void sendTo(Player* player, bool doClose = true);

	void decayWeapon(int decayRate);

	void setWeaponStats(int modifier);

	void sliceWeapon(Player* player);

	void repairWeapon(Player* player);

	void removePowerup(Player* player, bool notify);

	bool decreaseDot0Uses();

	bool decreaseDot1Uses();

	bool decreaseDot2Uses();

	bool decreasePowerupUses();

	bool isSliced();

	bool isJedi();

	bool isMelee();

	bool isRanged();

	bool isCertified();

	void powerupMinDamage(float powerupValue);

	void powerupMaxDamage(float powerupValue);

	void powerupHealthAttackCost(float powerupValue);

	void powerupActionAttackCost(float powerupValue);

	void powerupMindAttackCost(float powerupValue);

	void powerupWoundsRatio(float powerupValue);

	void powerupAttackSpeed(float powerupValue);

	void powerupPointBlankAccuracy(float powerupValue);

	void powerupIdealRange(float powerupValue);

	void powerupIdealAccuracy(float powerupValue);

	void powerupMaxRangeAccuracy(float powerupValue);

	void setDot0Uses(int uses);

	void setDot1Uses(int uses);

	void setDot2Uses(int uses);

	void setPowerupUses(int uses);

	void setCert(string& certification);

	void setCertified(bool crt);

	int getType();

	int getCategory();

	int getDamageType();

	float getMinDamage();

	float getMaxDamage();

	float getAttackSpeed();

	int getHealthAttackCost();

	int getActionAttackCost();

	int getMindAttackCost();

	int getPointBlankRange();

	int getPointBlankAccuracy();

	int getMaxRange();

	int getMaxRangeAccuracy();

	int getIdealRange();

	int getIdealAccuracy();

	int getWoundsRatio();

	int getArmorPiercing();

	int getDot0Type();

	int getDot0Attribute();

	int getDot0Strength();

	int getDot0Duration();

	int getDot0Potency();

	int getDot0Uses();

	int getDot1Type();

	int getDot1Attribute();

	int getDot1Strength();

	int getDot1Duration();

	int getDot1Potency();

	int getDot1Uses();

	int getDot2Type();

	int getDot2Attribute();

	int getDot2Strength();

	int getDot2Duration();

	int getDot2Potency();

	int getDot2Uses();

	int getSkillMod0Type();

	int getSkillMod1Type();

	int getSkillMod2Type();

	int getSkillMod0Value();

	int getSkillMod1Value();

	int getSkillMod2Value();

	int getPowerupUses();

	bool hasPowerup();

	string& getCert();

protected:
	string _return_getCert;

};

class WeaponImplementation;

class WeaponAdapter : public TangibleObjectAdapter {
public:
	WeaponAdapter(WeaponImplementation* impl);

	Packet* invokeMethod(sys::uint32 methid, ORBMethodInvocation* inv);

	void sendTo(Player* player, bool doClose);

	void decayWeapon(int decayRate);

	void setWeaponStats(int modifier);

	void sliceWeapon(Player* player);

	void repairWeapon(Player* player);

	void removePowerup(Player* player, bool notify);

	bool decreaseDot0Uses();

	bool decreaseDot1Uses();

	bool decreaseDot2Uses();

	bool decreasePowerupUses();

	bool isSliced();

	bool isJedi();

	bool isMelee();

	bool isRanged();

	bool isCertified();

	void powerupMinDamage(float powerupValue);

	void powerupMaxDamage(float powerupValue);

	void powerupHealthAttackCost(float powerupValue);

	void powerupActionAttackCost(float powerupValue);

	void powerupMindAttackCost(float powerupValue);

	void powerupWoundsRatio(float powerupValue);

	void powerupAttackSpeed(float powerupValue);

	void powerupPointBlankAccuracy(float powerupValue);

	void powerupIdealRange(float powerupValue);

	void powerupIdealAccuracy(float powerupValue);

	void powerupMaxRangeAccuracy(float powerupValue);

	void setDot0Uses(int uses);

	void setDot1Uses(int uses);

	void setDot2Uses(int uses);

	void setPowerupUses(int uses);

	void setCert(string& certification);

	void setCertified(bool crt);

	int getType();

	int getCategory();

	int getDamageType();

	float getMinDamage();

	float getMaxDamage();

	float getAttackSpeed();

	int getHealthAttackCost();

	int getActionAttackCost();

	int getMindAttackCost();

	int getPointBlankRange();

	int getPointBlankAccuracy();

	int getMaxRange();

	int getMaxRangeAccuracy();

	int getIdealRange();

	int getIdealAccuracy();

	int getWoundsRatio();

	int getArmorPiercing();

	int getDot0Type();

	int getDot0Attribute();

	int getDot0Strength();

	int getDot0Duration();

	int getDot0Potency();

	int getDot0Uses();

	int getDot1Type();

	int getDot1Attribute();

	int getDot1Strength();

	int getDot1Duration();

	int getDot1Potency();

	int getDot1Uses();

	int getDot2Type();

	int getDot2Attribute();

	int getDot2Strength();

	int getDot2Duration();

	int getDot2Potency();

	int getDot2Uses();

	int getSkillMod0Type();

	int getSkillMod1Type();

	int getSkillMod2Type();

	int getSkillMod0Value();

	int getSkillMod1Value();

	int getSkillMod2Value();

	int getPowerupUses();

	bool hasPowerup();

	string& getCert();

protected:
	string _param0_setCert__string_;
};

class WeaponHelper : public ORBClassHelper, public Singleton<WeaponHelper> {
public:
	WeaponHelper();

	void finalizeHelper();

	ORBObject* instantiateObject();

	ORBObjectAdapter* createAdapter(ORBObjectServant* obj);

	friend class SingletonWrapper<WeaponHelper>;
};

#include "../TangibleObjectImplementation.h"

class WeaponServant : public TangibleObjectImplementation {
public:
	Weapon* _this;

public:
	WeaponServant(unsigned long long oid, int tp);
	WeaponServant(unsigned long long oid, const unicode& name, const string& tempname, unsigned int tempcrc, int tp);
	virtual ~WeaponServant();

	void _setStub(ORBObjectStub* stub);
	ORBObjectStub* _getStub();

};

#endif /*WEAPON_H_*/

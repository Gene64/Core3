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

#include "../../../ZoneClient.h"
#include "../../player/Player.h"

#include "../../../packets.h"

#include "WeaponImplementation.h"

WeaponImplementation::WeaponImplementation(uint64 objid, uint32 tempCRC, const unicode& n, const string& tempn, bool eqp, int tp, int cat) 
		: WeaponServant(objid, n, tempn, tempCRC, WEAPON) {
	type = tp;
	setCategory(cat);
		
	equipped = eqp;

	initialize();
}

WeaponImplementation::WeaponImplementation(CreatureObject* creature, const string& temp, const unicode& n, const string& tempn, bool eqp, int tp, int cat) 
		: WeaponServant(creature->getNewItemID(), WEAPON) {
	objectCRC = String::hashCode(temp);

	name = n;
		
	type = tp;
	setCategory(cat);
		
	templateName = tempn;

	if (equipped = eqp)
		setContainer(creature, 0x04);
	else
		setContainer(creature->getInventory(), 0xFFFFFFFF);
		
	initialize();
}

void WeaponImplementation::initialize() {
	templateTypeName = "weapon_name";
	cert = "";
	certified = true;
	
	setMaxCondition(750);
	setConditionDamage(0);

	skillMod0Type = 0;
	skillMod0Value = 0;
	
	skillMod1Type = 0;
	skillMod1Value = 0;
	
	skillMod2Type = 0;
	skillMod2Value = 0;
	
	setDamageType(KINETIC);
	setMinDamage(50);
	setMaxDamage(100);
	
	setAttackSpeed(1.0f);
	
	setHealthAttackCost(15);
	setActionAttackCost(10);
	setMindAttackCost(5);
	
	setPointBlankRange(0);
	setPointBlankAccuracy(0);
	
	setIdealRange(2);
	setIdealAccuracy(15);
			
	setMaxRange(5);
	setMaxRangeAccuracy(0);
	
	setWoundsRatio(10);
	
	setArmorPiercing(NONE);
	
	dot0Type = 0;
	dot0Attribute = 0;
	dot0Strength = 0;
	dot0Duration = 0;
	dot0Potency = 0;
	dot0Uses = 0;
	
	dot1Type = 0;
	dot1Attribute = 0;
	dot1Strength = 0;
	dot1Duration = 0;
	dot1Potency = 0;
	dot1Uses = 0;

	dot2Type = 0;
	dot2Attribute = 0;
	dot2Strength = 0;
	dot2Duration = 0;
	dot2Potency = 0;
	dot2Uses = 0;
	
	powerupUses = 0;
	
	bonusMinDamage = 0;
	bonusMaxDamage = 0;
	bonusAttackSpeed = 0;
	bonusHealthAttackCost = 0;
	bonusActionAttackCost = 0;
	bonusMindAttackCost = 0;
	bonusPointBlankRange = 0;
	bonusPointBlankAccuracy = 0;
	bonusIdealRange = 0;
	bonusIdealAccuracy = 0;
	bonusMaxRange = 0;
	bonusMaxRangeAccuracy = 0;
	bonusWoundsRatio = 0;
	
	sliced = false;

	stringstream loggingname;
	loggingname << "Weapon = 0x" << objectID;
	setLoggingName(loggingname.str());
	
	setLogging(false);
	setGlobalLogging(true);
}

void WeaponImplementation::parseItemAttributes() {

	maxCondition = itemAttributes->getMaxCondition();
	conditionDamage = maxCondition - itemAttributes->getCurrentCondition();
	
	string name = "type";
	type = itemAttributes->getIntAttribute(name);
	
	name = "category";
	category = itemAttributes->getIntAttribute(name);
	
	name = "skillMod0Type";
	skillMod0Type = itemAttributes->getIntAttribute(name);
	name = "skillMod0Value";
	skillMod0Value = itemAttributes->getIntAttribute(name);

	name = "skillMod1Type";
	skillMod1Type = itemAttributes->getIntAttribute(name);
	name = "skillMod1Value";
	skillMod1Value = itemAttributes->getIntAttribute(name);
	
	name = "skillMod2Type";
	skillMod2Type = itemAttributes->getIntAttribute(name);
	name = "skillMod2Value";
	skillMod2Value = itemAttributes->getIntAttribute(name);
	
	name = "damageType";
	damageType = itemAttributes->getIntAttribute(name);
	
	name = "attackSpeed";
	attackSpeed = itemAttributes->getFloatAttribute(name);
	
	name = "healthCost";
	healthAttackCost = itemAttributes->getIntAttribute(name);
	name = "actionCost";
	actionAttackCost = itemAttributes->getIntAttribute(name);
	name = "mindCost";
	mindAttackCost = itemAttributes->getIntAttribute(name);

	name = "minDamage";
	minDamage = itemAttributes->getFloatAttribute(name);
	name = "maxDamage";
	maxDamage = itemAttributes->getFloatAttribute(name);
	
	name = "pointBlankRange";
	pointBlankRange = itemAttributes->getIntAttribute(name);
	name = "pointBlankAccuracy";
	pointBlankAccuracy = itemAttributes->getIntAttribute(name);
	
	name = "idealRange";
	idealRange = itemAttributes->getIntAttribute(name);
	name = "idealAccuracy";
	idealAccuracy = itemAttributes->getIntAttribute(name);
			
	name = "maxRange";
	maxRange = itemAttributes->getIntAttribute(name);
	name = "maxRangeAccuracy";
	maxRangeAccuracy = itemAttributes->getIntAttribute(name);
	
	name = "woundsRatio";
	woundsRatio = itemAttributes->getIntAttribute(name);
	
	name = "armorPiercing";
	armorPiercing = itemAttributes->getIntAttribute(name);
	
	name = "dot0Type";
	dot0Type = itemAttributes->getIntAttribute(name);
	name = "dot0Attribute";
	dot0Attribute = itemAttributes->getIntAttribute(name);
	name = "dot0Strength";
	dot0Strength = itemAttributes->getIntAttribute(name);
	name = "dot0Duration";
	dot0Duration = itemAttributes->getIntAttribute(name);
	name = "dot0Potency";
	dot0Potency = itemAttributes->getIntAttribute(name);
	name = "dot0Uses";
	dot0Uses = itemAttributes->getIntAttribute(name);

	name = "dot1Type";
	dot1Type = itemAttributes->getIntAttribute(name);
	name = "dot1Attribute";
	dot1Attribute = itemAttributes->getIntAttribute(name);
	name = "dot1Strength";
	dot1Strength = itemAttributes->getIntAttribute(name);
	name = "dot1Duration";
	dot1Duration = itemAttributes->getIntAttribute(name);
	name = "dot1Potency";
	dot1Potency = itemAttributes->getIntAttribute(name);
	name = "dot1Uses";
	dot1Uses = itemAttributes->getIntAttribute(name);

	name = "dot2Type";
	dot2Type = itemAttributes->getIntAttribute(name);
	name = "dot2Attribute";
	dot2Attribute = itemAttributes->getIntAttribute(name);
	name = "dot2Strength";
	dot2Strength = itemAttributes->getIntAttribute(name);
	name = "dot2Duration";
	dot2Duration = itemAttributes->getIntAttribute(name);
	name = "dot2Potency";
	dot2Potency = itemAttributes->getIntAttribute(name);
	name = "dot2Uses";
	dot2Uses = itemAttributes->getIntAttribute(name);

	name = "sliced";
	sliced = itemAttributes->getBooleanAttribute(name);
		
	name = "powerupUses";
	powerupUses = itemAttributes->getIntAttribute(name);
	
	name = "bonusAttackSpeed";
	bonusAttackSpeed = itemAttributes->getFloatAttribute(name);
	
	name = "bonusHealthAttackCost";
	bonusHealthAttackCost = itemAttributes->getIntAttribute(name);
	name = "bonusActionAttackCost";
	bonusActionAttackCost = itemAttributes->getIntAttribute(name);
	name = "bonusMindAttackCost";
	bonusMindAttackCost = itemAttributes->getIntAttribute(name);

	name = "bonusMinDamage";
	bonusMinDamage = itemAttributes->getFloatAttribute(name);
	name = "bonusMaxDamage";
	bonusMaxDamage = itemAttributes->getFloatAttribute(name);
	
	name = "bonusPointBlankRange";
	bonusPointBlankRange = itemAttributes->getIntAttribute(name);
	name = "bonusPointBlankAccuracy";
	bonusPointBlankAccuracy = itemAttributes->getIntAttribute(name);
	
	name = "bonusIdealRange";
	bonusIdealRange = itemAttributes->getIntAttribute(name);
	name = "bonusIdealAccuracy";
	bonusIdealAccuracy = itemAttributes->getIntAttribute(name);
			
	name = "bonusMaxRange";
	bonusMaxRange = itemAttributes->getIntAttribute(name);
	
	name = "bonusMaxRangeAccuracy";
	bonusMaxRangeAccuracy = itemAttributes->getIntAttribute(name);
	
	name = "bonusWoundsRatio";
	bonusWoundsRatio = itemAttributes->getIntAttribute(name);

	name = "cert";
	cert = itemAttributes->getStringAttribute(name);
}

void WeaponImplementation::sendTo(Player* player, bool doClose) {
	ZoneClient* client = player->getClient();
	if (client == NULL)
		return;

	SceneObjectImplementation::create(client);
	
	if (container != NULL)
		link(client, container);
	
	BaseMessage* weao3 = new WeaponObjectMessage3((Weapon*) _this);
	client->sendMessage(weao3);

	/*Message* weao6 = new WeaponObjectMessage6(this);
	client->sendMessage(weao6);*/
	
	if (doClose)
		SceneObjectImplementation::close(client);
}

void WeaponImplementation::generateAttributes(SceneObject* obj) {
	if (!obj->isPlayer())
		return;
		
	Player* player = (Player*) obj;
	
	AttributeListMessage* alm = new AttributeListMessage((Weapon*) _this);
	
	if (player->checkCertification(cert))
		alm->insertAttribute("weapon_cert_status", "Yes");
	else
		alm->insertAttribute("weapon_cert_status", "No");
	
	stringstream cond;
	cond << (maxCondition-conditionDamage) << "/" << maxCondition;
	
	alm->insertAttribute("condition", cond);
	
	alm->insertAttribute("volume", "1");
	
	if (skillMod0Type > 0)
		generateSkillMods(alm, skillMod0Type, skillMod0Value);
	
	if (skillMod1Type > 0)
		generateSkillMods(alm, skillMod1Type, skillMod1Value);
	
	if (skillMod2Type > 0)
		generateSkillMods(alm, skillMod2Type, skillMod2Value);

	string ap;
	
	switch (armorPiercing) {
	case NONE:
		ap = "None";
		break;
	case LIGHT:
		ap = "Light";
		break;
	case MEDIUM:
		ap = "Medium";
		break;
	case HEAVY:
		ap = "Heavy";
		break;
	default:
		ap = "Unknown";
		break;
	}
	
	alm->insertAttribute("wpn_armor_pierce_rating", ap);
	
	float speed = round(10 * getAttackSpeed()) / 10;
	
	stringstream spdtxt;
	
	spdtxt << speed;
	
	if ((int(round(speed * 10)) % 10) == 0)
		spdtxt << ".0";
	
	alm->insertAttribute("wpn_attack_speed", spdtxt.str());
	
	//Damage Information
	stringstream dmgtxt;

	switch (damageType) {
	case KINETIC:
		dmgtxt << "Kinetic";
		break;
	case ENERGY:
		dmgtxt << "Energy";
		break;
	case ELECTRICITY:
		dmgtxt << "Electricity";
		break;
	case STUN:
		dmgtxt << "Stun";
		break;
	case BLAST:
		dmgtxt << "Blast";
		break;
	case HEAT:
		dmgtxt << "Heat";
		break;
	case COLD:
		dmgtxt << "Cold";
		break;
	case ACID:
		dmgtxt << "Acid";
		break;
	case LIGHTSABER:
		dmgtxt << "Lightsaber";
		break;
	}
	
	alm->insertAttribute("damage.wpn_damage_type", dmgtxt);

	float minDmg = round(getMinDamage());
	float maxDmg = round(getMaxDamage());
	
	alm->insertAttribute("damage.wpn_damage_min", minDmg);

	alm->insertAttribute("damage.wpn_damage_max", maxDmg);
	
	stringstream woundsratio;
	woundsratio << getWoundsRatio() << "%";
	
	alm->insertAttribute("damage.wpn_wound_chance", woundsratio);
	
	//Accuracy Modifiers
	stringstream pblank;
	if (getPointBlankAccuracy() >= 0)
		pblank << "+";
		
	pblank << getPointBlankAccuracy() << " @ " << getPointBlankRange() << "m";
	alm->insertAttribute("cat_wpn_rangemods.wpn_range_zero", pblank);
	
	stringstream ideal;
	if (getIdealAccuracy() >= 0)
		ideal << "+";
		
	ideal << getIdealAccuracy() << " @ " << getIdealRange() << "m";
	alm->insertAttribute("cat_wpn_rangemods.wpn_range_mid", ideal);
	
	stringstream maxrange;
	if (getMaxRangeAccuracy() >= 0)
		maxrange << "+";
		
	maxrange << getMaxRangeAccuracy() << " @ " << getMaxRange() << "m";
	alm->insertAttribute("cat_wpn_rangemods.wpn_range_max", maxrange);
	
	//Special Attack Costs
	alm->insertAttribute("cat_wpn_attack_cost.health", getHealthAttackCost());
	
	alm->insertAttribute("cat_wpn_attack_cost.action", getActionAttackCost());
	
	alm->insertAttribute("cat_wpn_attack_cost.mind", getMindAttackCost());
	
	if (dot0Uses !=0 || dot1Uses != 0 || dot2Uses != 0)
		generateDotAttributes(alm);
	
	if (sliced == 1) 
		alm->insertAttribute("hacked1", "");
	
	generatePowerup(alm);
	
	player->sendMessage(alm);
}

void WeaponImplementation::generateDotAttributes(AttributeListMessage* alm) {
	if (dot0Uses != 0) {
		//Sends the information along for the first DOT, if it exists
		
		switch (dot0Type) {
		case BLEED:
			alm->insertAttribute("cat_wpn_dot_00.wpn_dot_type", "Bleed");
			break;
		case DISEASE:
			alm->insertAttribute("cat_wpn_dot_00.wpn_dot_type", "Disease");
			break;
		case FIRE:
			alm->insertAttribute("cat_wpn_dot_00.wpn_dot_type", "Fire");
			break;
		case POISON:
			alm->insertAttribute("cat_wpn_dot_00.wpn_dot_type", "Poison");
			break;
		}
		
		switch (dot0Attribute) {
		case HEALTH:
			alm->insertAttribute("cat_wpn_dot_00.wpn_dot_attrib", "Health");
			break;
		case STRENGTH:
			alm->insertAttribute("cat_wpn_dot_00.wpn_dot_attrib", "Strength");
			break;
		case CONSTITUTION:
			alm->insertAttribute("cat_wpn_dot_00.wpn_dot_attrib", "Constitution");
			break;
		case ACTION:
			alm->insertAttribute("cat_wpn_dot_00.wpn_dot_attrib", "Action");
			break;
		case QUICKNESS:
			alm->insertAttribute("cat_wpn_dot_00.wpn_dot_attrib", "Quickness");
			break;
		case STAMINA:
			alm->insertAttribute("cat_wpn_dot_00.wpn_dot_attrib", "Stamina");
			break;
		case MIND:
			alm->insertAttribute("cat_wpn_dot_00.wpn_dot_attrib", "Mind");
			break;
		case FOCUS:
			alm->insertAttribute("cat_wpn_dot_00.wpn_dot_attrib", "Focus");
			break;
		case WILLPOWER:
			alm->insertAttribute("cat_wpn_dot_00.wpn_dot_attrib", "Willpower");
			break;
		}
		alm->insertAttribute("cat_wpn_dot_00.wpn_dot_strength", dot0Strength);
		
		stringstream dur;
		dur << dot0Duration << "s";
		alm->insertAttribute("cat_wpn_dot_00.wpn_dot_duration", dur);
		
		stringstream pot;
		pot << dot0Potency << "%";
		alm->insertAttribute("cat_wpn_dot_00.wpn_dot_potency", pot);
		
		alm->insertAttribute("cat_wpn_dot_00.wpn_dot_uses", dot0Uses);
	}

	if (dot1Uses != 0) {
		//Sends the information for the second DOT, if it exists
		
		switch (dot1Type) {
		case BLEED:
			alm->insertAttribute("cat_wpn_dot_01.wpn_dot_type", "Bleed");
			break;
		case DISEASE:
			alm->insertAttribute("cat_wpn_dot_01.wpn_dot_type", "Disease");
			break;
		case FIRE:
			alm->insertAttribute("cat_wpn_dot_01.wpn_dot_type", "Fire");
			break;
		case POISON:
			alm->insertAttribute("cat_wpn_dot_01.wpn_dot_type", "Poison");
			break;
		}
		
		switch (dot1Attribute) {
		case HEALTH:
			alm->insertAttribute("cat_wpn_dot_01.wpn_dot_attrib", "Health");
			break;
		case STRENGTH:
			alm->insertAttribute("cat_wpn_dot_01.wpn_dot_attrib", "Strength");
			break;
		case CONSTITUTION:
			alm->insertAttribute("cat_wpn_dot_01.wpn_dot_attrib", "Constitution");
			break;
		case ACTION:
			alm->insertAttribute("cat_wpn_dot_01.wpn_dot_attrib", "Action");
			break;
		case QUICKNESS:
			alm->insertAttribute("cat_wpn_dot_01.wpn_dot_attrib", "Quickness");
			break;
		case STAMINA:
			alm->insertAttribute("cat_wpn_dot_01.wpn_dot_attrib", "Stamina");
			break;
		case MIND:
			alm->insertAttribute("cat_wpn_dot_01.wpn_dot_attrib", "Mind");
			break;
		case FOCUS:
			alm->insertAttribute("cat_wpn_dot_01.wpn_dot_attrib", "Focus");
			break;
		case WILLPOWER:
			alm->insertAttribute("cat_wpn_dot_01.wpn_dot_attrib", "Willpower");
			break;
		}
		
		alm->insertAttribute("cat_wpn_dot_01.wpn_dot_strength", dot1Strength);

		stringstream dur;
		dur << dot1Duration << "s";
		alm->insertAttribute("cat_wpn_dot_01.wpn_dot_duration", dur);
		
		stringstream pot;
		pot << dot1Potency << "%";
		alm->insertAttribute("cat_wpn_dot_01.wpn_dot_potency", pot);
		
		alm->insertAttribute("cat_wpn_dot_01.wpn_dot_uses", dot1Uses);
	}
	
	if (dot2Uses != 0) {
		//The third DOT, if it exists
		
		switch (dot2Type) {
		case BLEED:
			alm->insertAttribute("cat_wpn_dot_02.wpn_dot_type", "Bleed");
			break;
		case DISEASE:
			alm->insertAttribute("cat_wpn_dot_02.wpn_dot_type", "Disease");
			break;
		case FIRE:
			alm->insertAttribute("cat_wpn_dot_02.wpn_dot_type", "Fire");
			break;
		case POISON:
			alm->insertAttribute("cat_wpn_dot_02.wpn_dot_type", "Poison");
			break;
		}
		
		switch (dot2Attribute) {
		case HEALTH:
			alm->insertAttribute("cat_wpn_dot_02.wpn_dot_attrib", "Health");
			break;
		case STRENGTH:
			alm->insertAttribute("cat_wpn_dot_02.wpn_dot_attrib", "Strength");
			break;
		case CONSTITUTION:
			alm->insertAttribute("cat_wpn_dot_02.wpn_dot_attrib", "Constitution");
			break;
		case ACTION:
			alm->insertAttribute("cat_wpn_dot_02.wpn_dot_attrib", "Action");
			break;
		case QUICKNESS:
			alm->insertAttribute("cat_wpn_dot_02.wpn_dot_attrib", "Quickness");
			break;
		case STAMINA:
			alm->insertAttribute("cat_wpn_dot_02.wpn_dot_attrib", "Stamina");
			break;
		case MIND:
			alm->insertAttribute("cat_wpn_dot_02.wpn_dot_attrib", "Mind");
			break;
		case FOCUS:
			alm->insertAttribute("cat_wpn_dot_02.wpn_dot_attrib", "Focus");
			break;
		case WILLPOWER:
			alm->insertAttribute("cat_wpn_dot_02.wpn_dot_attrib", "Willpower");
			break;
		}
		
		alm->insertAttribute("cat_wpn_dot_02.wpn_dot_strength", dot2Strength);
		
		stringstream dur;
		dur << dot2Duration << "s";
		alm->insertAttribute("cat_wpn_dot_02.wpn_dot_duration", dur);
		
		stringstream pot;
		pot << dot2Potency << "%";
		alm->insertAttribute("cat_wpn_dot_02.wpn_dot_potency", pot);
		
		alm->insertAttribute("cat_wpn_dot_02.wpn_dot_uses", dot2Uses);
	}
}

void WeaponImplementation::decayWeapon(int decayRate) {

	setConditionDamage(conditionDamage + (maxCondition * decayRate / 100));

	if (conditionDamage > maxCondition)
		setConditionDamage(maxCondition);
	
	if (maxCondition > 0) {
		float ratio = ((float) conditionDamage) / ((float) maxCondition);

		if (ratio > 0.99) {
			setMaxCondition(1);
			setConditionDamage(1);
			setMaxDamage(0);
			setMinDamage(0);
		} else if (ratio > 0.75) {
			setMaxDamage(maxDamage - (maxDamage * decayRate / 100));
			setMinDamage(minDamage - (minDamage * decayRate / 100));

			setAttackSpeed(attackSpeed + (attackSpeed * decayRate / 100));
		}
	}
	
	updated = true;
	
}

void WeaponImplementation::repairWeapon(Player* player) {
	int roll = System::random(100);
	
	int decayRate = 0;
	
	stringstream txt;
	
	if (roll < 10) {
		player->sendSystemMessage("You have completely failed to repair the item. The item falls apart.");
		decayWeapon(100);
		
		updated = true;
		
		TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(_this);
		dtano3->updateConditionDamage();
		dtano3->updateMaxCondition();
		dtano3->close();
		player->broadcastMessage(dtano3);
		
		generateAttributes(player);
		
		return;
	} else if (roll < 75) {
		txt << "You have repaired the item, however the items maximum condition has been reduced.";
		decayRate = 20;
	} else {
		txt << "You have completely repaired the item.";				
	}
	
	player->sendSystemMessage(txt.str());

	setMaxCondition(maxCondition - (maxCondition / 100 * decayRate));
	setConditionDamage(0);
	
	updated = true;
		
	TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(_this);
	dtano3->updateConditionDamage();
	dtano3->updateMaxCondition();
	dtano3->close();
	player->broadcastMessage(dtano3);
}

void WeaponImplementation::setWeaponStats(int modifier){
	wlock();
	
	int luck = (System::random(100)) + (modifier/4);
	
	if (System::random(1000) == 7) 
		luck = luck * 2; 
	
	if (System::random(50000) == 77) 
		luck = luck * 5; 
		
	if (System::random(1000000) == 777) 
		luck = luck * 10; 
	
	if (System::random(100) == 6) 
		luck = 0;
		
	modifier = modifier + System::random(10);
	
	int playerRoll = System::random(1000) * modifier * luck / 1000;
	if (playerRoll > 200000) {
		modifier = modifier + 100;
		luck = luck + 150;
		setMaxDamage(maxDamage * 1.5);
		
		stringstream itemText;
		itemText << "\\#ffff00" << name.c_str() << " (Legendary)";
		name = unicode(itemText.str());
	} else if (playerRoll > 55000) {
		modifier = modifier + 50;
		luck = luck + 100;

		stringstream itemText;
		itemText << "\\#ffff00" << name.c_str() << " (Exceptional)";	
		name = unicode(itemText.str());
	} else if (playerRoll > 12500) {
		modifier = modifier + 25;
		luck = luck + 50;

		stringstream itemText;
		itemText << "\\#ffff00" << name.c_str();
		name = unicode(itemText.str());
	}
	
	if (luck * System::random(100) > 1700) {
		setMinDamage(minDamage + (minDamage * luck / 157.93f));
		setMaxDamage(maxDamage + (maxDamage * luck / 159.11f));
	}
	
	if (luck * System::random(100) > 1700) {	
		setAttackSpeed(attackSpeed - (attackSpeed * luck / 357.69f));
	}
	
	if (luck * System::random(100) > 1700) {
		setHealthAttackCost(healthAttackCost - (healthAttackCost * luck / 359));
		setActionAttackCost(actionAttackCost - (actionAttackCost * luck / 359));
		setMindAttackCost(mindAttackCost - (mindAttackCost * luck / 359));
	}

	if (luck * System::random(100) > 1700)
		setWoundsRatio(woundsRatio + (modifier / 15) + (luck / 10));
	
	if (playerRoll > 12500 && System::random(3) == 1) {
		setSkillMod0Type(System::random(30) + 1);
		setSkillMod0Value(luck / (System::random(3) + 10));
	}
	if (playerRoll > 25000 && System::random(2) == 1) {
		setSkillMod1Type(System::random(30) + 1);
		setSkillMod1Value(luck / (System::random(3) + 10));
	}
	if (playerRoll > 45000) {
		setSkillMod2Type(System::random(30) + 1);
		setSkillMod2Value(luck / (System::random(3) + 10));
	}
	
	if (playerRoll > 13500 && System::random(1) == 1)	{
		switch (System::random(4)) {
		case 1:
			setDot1Type(BLEED);
			setDot1Attribute((System::random(2) * 3) + 1);
			setDot1Strength((modifier / 13) + (luck / 2));
			setDot1Duration(((luck * 4) + modifier) / 7);
			setDot1Potency(System::random(luck / 3) + (luck / 5));
			setDot1Uses((modifier + luck) * 11);
			break;
		case 2:
			setDot1Type(DISEASE);
			setDot1Attribute((System::random(2) * 3) + 1);
			setDot1Strength((modifier / 13) + (luck / 2));
			setDot1Duration(((luck * 4) + modifier) / 7);
			setDot1Potency(System::random(luck / 3) + (luck / 5));
			setDot1Uses((modifier + luck) * 11);
			break;
		case 3:
			setDot1Type(FIRE);
			setDot1Attribute((System::random(2) * 3) + 1);
			setDot1Strength((modifier / 13) + (luck / 2));
			setDot1Duration(((luck * 4) + modifier) / 7);
			setDot1Potency(System::random(luck / 3) + (luck / 5));
			setDot1Uses((modifier + luck) * 11);
			break;
		case 4:
			setDot1Type(POISON);
			setDot1Attribute((System::random(2) * 3) + 1);
			setDot1Strength((modifier / 13) + (luck / 2));
			setDot1Duration(((luck * 4) + modifier) / 7);
			setDot1Potency(System::random(luck / 3) + (luck / 5));
			setDot1Uses((modifier + luck) * 11);
			break;
		}
	}
	
	if (attackSpeed < 1) 
		setAttackSpeed(1.0f);
	
	if (healthAttackCost < 0) 
		setHealthAttackCost(0);
	
	if (actionAttackCost < 0) 
		setActionAttackCost(0);
	
	if (mindAttackCost < 0) 
		setMindAttackCost(0);
	
	if (objectSubType == TangibleObjectImplementation::SPECIALHEAVYWEAPON && maxDamage > 1100)
		setMaxDamage(1050 + System::random(50));
		
	else if (objectSubType == TangibleObjectImplementation::MELEEWEAPON && maxDamage > 500)
		setMaxDamage(450 + System::random(50));

	else if (maxDamage > 900)
		setMaxDamage(850 + System::random(50));
	
	if (dot1Strength > 300)
		setDot1Strength(250 + System::random(50));
	
	if (minDamage > maxDamage) 
		setMinDamage(round(0.8 * maxDamage));
	
	if (skillMod0Value > 25)
		setSkillMod0Value(25);

	if (skillMod1Value > 25)
		setSkillMod1Value(25);

	if (skillMod2Value > 25)
		setSkillMod2Value(25);
	
	if (skillMod2Type == skillMod1Type || skillMod2Type == skillMod0Type) {
		setSkillMod2Type(0);
		setSkillMod2Value(0);
	}
	
	if (skillMod1Type == skillMod0Type || skillMod1Type == skillMod2Type) {
		setSkillMod1Type(0);
		setSkillMod1Value(0);
	}
	
	equipped = false;
	
	persistent = false;
	updated = true;
	
	unlock();
}

void WeaponImplementation::generatePowerup(AttributeListMessage* alm) {
	
	if (powerupUses != 0) {
		alm->insertAttribute("cat_pup.pup_uses", powerupUses);
		
		if (bonusMinDamage != 0) {
			stringstream txt;
			txt << "+" << round(bonusMinDamage);
			alm->insertAttribute("cat_pup.pup_wpn_damage_min", txt.str());
		}
		if (bonusMaxDamage != 0) {
			stringstream txt;
			txt << "+" << round(bonusMaxDamage);
			alm->insertAttribute("cat_pup.pup_wpn_damage_max", txt.str());
		}
		if (bonusAttackSpeed != 0) {
			
			float spd = bonusAttackSpeed;
			
			stringstream spdtxt;
			
			spdtxt << round(10*spd)/10;
			
			if ((int(round(spd * 10)) % 10) == 0)
				spdtxt << ".0";
			
			stringstream txt;
			txt << round(10*bonusAttackSpeed)/10;
			alm->insertAttribute("cat_pup.pup_wpn_attack_speed", spdtxt.str());
		}
		if (bonusHealthAttackCost != 0)
			alm->insertAttribute("cat_pup.pup_wpn_attack_cost_health", bonusHealthAttackCost);

		if (bonusActionAttackCost != 0)
			alm->insertAttribute("cat_pup.pup_wpn_attack_cost_action", bonusActionAttackCost);
			
		if (bonusMindAttackCost != 0)
			alm->insertAttribute("cat_pup.pup_wpn_attack_cost_mind", bonusMindAttackCost);
		
		if (bonusPointBlankAccuracy != 0) {
			stringstream txt;
			txt << "+" << bonusPointBlankAccuracy;
			alm->insertAttribute("cat_pup.pup_wpn_range_attack_mod_zero", txt.str());
		}
		if (bonusIdealRange != 0)
			alm->insertAttribute("cat_pup.pup_wpn_range_mid", bonusIdealRange);
			
		if (bonusIdealAccuracy != 0) {
			stringstream txt;
			txt << "+" << bonusIdealAccuracy;
			alm->insertAttribute("cat_pup.pup_wpn_range_attack_mod_mid", txt.str());
		}
		if (bonusMaxRangeAccuracy != 0) {
			stringstream txt;
			txt << "+" << bonusMaxRangeAccuracy;
			alm->insertAttribute("cat_pup.pup_wpn_range_attack_mod_max", txt.str());
		}
		if (bonusWoundsRatio != 0) {
			stringstream txt;
			txt << "+" << bonusWoundsRatio << "%";
			alm->insertAttribute("cat_pup.pup_wpn_wound_chance", txt.str());
		}
	}
}

void WeaponImplementation::sliceWeapon(Player* player){
	bool sliceType = System::random(1);
	int slicePercent;
	
	int min = 0;
	int max = 0;
	
	stringstream msg;

	try {
		wlock();

		if (!isSliced()) {
			
			int sliceSkill = player->getSlicingAbility();
			switch (sliceSkill) {
			case 2 :
			case 3 :
				min = 10;
				max = 25;
				break;
			case 4 :
				min = 10;
				max = 30;
				break;
			case 5 :
				min = 15;
				max = 35;
				break;
			default :
				break;
			}
			
			removePowerup(player, false);
			switch (sliceType) {
			case 0:
				slicePercent = sliceWeaponDamage(min, max);
				msg << "Weapon damage increased by " << slicePercent << "%";
				break;
			case 1:
				slicePercent = sliceWeaponSpeed(min, max);
				msg << "Weapon speed decreased by " << slicePercent << "%";
				break;
			}
			
			generateAttributes(player);

		} else
			msg << "Weapon is already sliced.";

		unlock();
	} catch (...) {
		unlock();
	}

	player->sendSystemMessage(msg.str());
}

int WeaponImplementation::sliceWeaponDamage(int min, int max){
	if (sliced) 
		return 0;
		
	int modifier = System::random(max - min) + min;
	
	setMinDamage((minDamage * modifier / 100) + minDamage);
	setMaxDamage((maxDamage * modifier / 100) + maxDamage);
	
	setSliced(true);
	updated = true;
	
	return modifier;
}

int WeaponImplementation::sliceWeaponSpeed(int min, int max){
	if (sliced) 
		return 0;
		
	int modifier = System::random(max - min) + min;
	
	setAttackSpeed(attackSpeed - (attackSpeed * modifier / 100));

	if (attackSpeed < 1) 
		setAttackSpeed(1.0f);
	
	setSliced(true);
	updated = true;
	
	return modifier;
}

void WeaponImplementation::powerupMinDamage(float powerupValue) {
	setBonusMinDamage(minDamage * powerupValue / 100.0f);

	if (getMinDamage() > getMaxDamage())
		setBonusMinDamage(getMaxDamage() - minDamage - 1);
}

void WeaponImplementation::powerupMaxDamage(float powerupValue) {
	setBonusMaxDamage(maxDamage * powerupValue / 100.0f);
}

void WeaponImplementation::powerupHealthAttackCost(float powerupValue) {
	setBonusHealthAttackCost(int(-healthAttackCost * powerupValue / 100.0f));
}

void WeaponImplementation::powerupActionAttackCost(float powerupValue) {
	setBonusActionAttackCost(int(-actionAttackCost * powerupValue / 100.0f));
}

void WeaponImplementation::powerupMindAttackCost(float powerupValue) {
	setBonusMindAttackCost(int(-mindAttackCost * powerupValue / 100.0f));
}

void WeaponImplementation::powerupWoundsRatio(float powerupValue) {
	setBonusWoundsRatio(int(woundsRatio * powerupValue / 100.0f));
}

void WeaponImplementation::powerupAttackSpeed(float powerupValue) {
	setBonusAttackSpeed(-attackSpeed * powerupValue / 100.0f);
}

void WeaponImplementation::powerupPointBlankAccuracy(float powerupValue) {
	if (pointBlankAccuracy < 0)
		setBonusPointBlankAccuracy(int((float)-pointBlankAccuracy * powerupValue / 100.0f));
	else
		setBonusPointBlankAccuracy(int((float)pointBlankAccuracy * powerupValue / 100.0f));
}

void WeaponImplementation::powerupIdealRange(float powerupValue) {
	int idealRang = int((float)-idealRange * powerupValue / 100.0f);
		
	setBonusIdealRange(idealRang);
}

void WeaponImplementation::powerupIdealAccuracy(float powerupValue) {
	if (idealAccuracy < 0)
		setBonusIdealAccuracy(int((float)-idealAccuracy * powerupValue / 100.0f));
	else
		setBonusIdealAccuracy(int((float)idealAccuracy * powerupValue / 100.0f));
}

void WeaponImplementation::powerupMaxRangeAccuracy(float powerupValue) {
	if (maxRangeAccuracy < 0)
		setBonusMaxRangeAccuracy(int((float)-maxRangeAccuracy * powerupValue / 100.0f));
	else
		setBonusMaxRangeAccuracy(int((float)maxRangeAccuracy * powerupValue / 100.0f));
}

void WeaponImplementation::removePowerup(Player* player, bool notify) {
	setPowerupUses(0);
	
	setBonusMinDamage(0);
	setBonusMaxDamage(0);
	setBonusAttackSpeed(0);
	setBonusHealthAttackCost(0);
	setBonusActionAttackCost(0);
	setBonusMindAttackCost(0);
	setBonusPointBlankRange(0);
	setBonusPointBlankAccuracy(0);
	setBonusIdealRange(0);
	setBonusIdealAccuracy(0);
	setBonusMaxRange(0);
	setBonusMaxRangeAccuracy(0);
	setBonusWoundsRatio(0);
	
	if (notify) {
		stringstream txt;
		txt << "The powerup on your " << name.c_str() << " has expired.";
		player->sendSystemMessage(txt.str());
	}
	
	generateAttributes(player);
}

//#include <gtest/gtest.h>
//
//#include "CombatSystem.h"
//#include "Player.h"
//#include "Enemy.h"
//
//TEST(CombatSystemTests, AttackDealsCorrectDamage)
//{
//    Player player;
//    Enemy enemy(EnemyType::Slime);
//
//    player.setStrength(5);
//    enemy.setDefense(2);
//
//    CombatSystem combat;
//
//    CombatResult result =
//        combat.attack(player, enemy);
//
//    EXPECT_EQ(result.damage, 3);
//}
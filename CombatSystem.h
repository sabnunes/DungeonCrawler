#pragma once

/*
Combat rules are currently duplicated.
The damage bug becomes easier to test.
You can unit test combat without running the whole game.
It shows separation of rules from presentation.

Conceptually, CombatSystem should answer questions like :

How much damage does attacker deal ?
Did the defender die ?
What stat changes happen after defeat ?

But it should not print UI text.That should remain outside or be returned as events / messages.
*/


class CombatSystem
{
};


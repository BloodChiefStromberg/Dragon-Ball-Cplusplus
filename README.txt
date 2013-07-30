WELCOME TO DRAGON BALL C++

You're Goku. Picolo dared you to go into some caves, so you did. But there was
danger! Prepare to fight!

Main Controls:
8 = up
2 = down
4 = left
6 = right
u = use
p = pick-up
s = ascend/descend stairs
q = quit

Notes:

Going up from the first level quits the game and prints out your score. Score 
right now is calculated by current XP * level. Dying will also print out your 
score. Later, I want score to be about how good of loot you have. So I'll get
all the characters loot, and do (100 - item->getRarity()) to generate how rare
the items are. The more rare Items you collect, the better your score.

Creatures all start with Default Weapon and Default Armor. They suck. I'm working
on a program called Itemerizer (Itemerizer.cpp) to allow the user to create
some Items, but really, I made it for me. I'll use it to make Weapons, Armor,
and Potions. However, to make it, I'm also creating a menu system.

There is a basic menu system used to display your inventory and use items (I
give the player a Red Potion to start, just to demonstrate how items will work),
but it's not flexible at all, and couldn't be extended for the Itemerizer.

ON LOOT:
When items are dropped, they appear as their Display character says they should.
However, if there is a RoomTile with more than one item on it, the whole stack
will display as the character 'L'oot. 

The ammount of loot you can hold is not currently limited at all, so the menu
displayed when you have too much can get kind of ugly.

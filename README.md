# LostSpace  :space_invader:

Small conversational game in the style of Zork made by [Miquel Prieto Moliné](https://github.com/MacXxs) </br>
You can check the repo [here](https://github.com/MacXxs/LostSpace) </br>

## Table of Contents 
- [Game Commands](https://github.com/MacXxs/LostSpace/edit/master/README.md#game-commands)               
</t> 1. [Interaction Commands](https://github.com/MacXxs/LostSpace/edit/master/README.md#interaction-commands)  
</t> 2. [Movement Commands](https://github.com/MacXxs/LostSpace/edit/master/README.md#movement-commands) </br>
</t> 3. [Important Information](https://github.com/MacXxs/LostSpace/edit/master/README.md#important-information) 
- [Quick Guide](https://github.com/MacXxs/LostSpace/edit/master/README.md#quick-guide)

## Game Commands
### Interaction Commands
- The **LOOK** command prints a description of your surroundings. You can use the **LOOK** command followed by the name of an entity in the room to get a description of that entity alone. </br> Usage: </br>  ```> LOOK``` </br> ```> LOOK entity_name```
- The **INVENTORY** command prints a description of the items in your inventory. </br> Usage: </br> ```> INVENTORY```
- The **OPEN** commmand prints a descriptions of the items contained inside a container. </br> Usage: </br> ```> OPEN container_name```
- The **GRAB** commmand allows you to grab items and store them in you inventory. </br> Usage: </br> ```> GRAB item_name```
- The **DROP** command allows you to drop items from your backpack on the room you're in. </br> Usage: </br> ```> DROP item_name```
- The **USE** command allows you to use items from your backpack or your surroudings. </br> Only recordings and terminals can be used without having them in your inventory. </br> Usage: </br> ```> USE item_name``` </br> ```> USE item_name ON entity_name```
- The **PLACE** command allows you to place an item from your inventory inside a container. </br> Usage: </br> ```> PLACE item_name IN container_name```
- The **CONSUME** command allows you to drink or eat a consumable item. </br> Usage: </br> ```> CONSUME consumable_name```
- The **ATTACK** command allows you attack with your fists an auto-targeted enemy, attack an enemy in particular whith your fists or attack an enemy in particular using a weapon from your inventory. </br> Usage: </br> ```> ATTACK``` </br> ```> ATTACK enemy_name``` </br> ```> ATTACK enemy_name WITH weapon_name```
### Movement Commands
- To walk in a direction just type the direction you wanna move: </br>
```> NORTH``` </br> ```> SOUTH``` </br> ```> EAST``` </br> ```> WEST``` </br> ```> UP``` </br> ```> DOWN```
### Important Information
- Items must be referred by their full name, if an item is labeled "penaut_butter" and you want to get a closer look at it, you must type: </br> ```> LOOK PENAUT_BUTTER```
- It doesn't matter if you use lower or upper cases while typing.
- Use the **QUIT** command to exit the game. </br> ```> QUIT```

## Quick Guide
1. Grab the **backpack**
2. Open the **lockers** and grab the **universal_key**
3. Use the **universal_key** on the **automatic_door**
4. Go **west**
5. Grab the **spaghetti** and the **menstor** if you wanna have a health item and an armor boost.
6. Go **up**
7. Use the **audiolog** if you wanna know what happened while you where in cryosleep, drop the **universal_key** (you won't need it anymore) and grab the **plasma_cutter**
8. Go **down** and then **west**
9. Grab the **severed_hand** (drop something so you can grab the hand, you can later drop the hand and grab back whatever you dropped)
10. Go **down**
11. Use the **flashlight** so you can see around you.
12. Use the **severed_hand** on the **security_terminal** and drop the hand (you no longer need it)
13. Go **up**
14. Grab wathever you droped before so you could take the hand
15. Go **west**
16. Kill the **alien**. You can attack him with the **plasma_cutter** to increase your damage. Also, you can consume the **spaghetti** (to recover **health**) or the **menstor** (to gain an armor bonus for 10 moves). 
17. Use the **onboard_computer**
18. FIN

Fix player landing on floor and elevated platforms: detect crossing tile top even when feet start exactly on it. Previously new_foot % 16 == 0 missed a step from feet=192 to 193.

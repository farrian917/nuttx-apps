# Player one-way platform collision fix

The player now passes through elevated platforms while rising and lands on their top surfaces when falling. The bottom two tile rows remain solid ground. Enemy collision and patrol are unchanged.

Replace your existing apps/games/nx2d directory, rebuild NuttX, and test jumping up through platforms and landing on them.

Note: one-way behavior applies to every tile above the bottom two rows in the demo level. For future levels, add a dedicated ONE_WAY tile ID rather than using tile height to distinguish platforms.

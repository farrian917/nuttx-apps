# Enemy platform collision fix

Enemies previously spawned at a hardcoded y=160, even when this put their 16x32 collision boxes inside elevated platforms. They now spawn at the first valid standing position at their X coordinate, checking both feet, and search nearby X coordinates if necessary. Enemy patrol checks support under both feet to avoid walking off platform edges. No changes to Xbox input, renderer, sprite format, or weapons.

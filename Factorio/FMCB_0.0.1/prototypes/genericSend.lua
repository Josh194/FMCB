local genSend = table.deepcopy(data.raw.container)

script.onPlaced({defines.events.on_built_entity},
   function (e)
		--External Function
		registerSend(e.created_entity)
   end
)

script.onDestroyed({defines.events.on_pre_player_mined_item},
   function (e)
		--External Function
		unregisterSend(e.entity)
   end
) 
script.on_event({defines.events.on_tick},
   function (e)
      if e.tick == 0 then
        game.print("FMCB has been correctly loaded")

        local chest_inventory = entity.get_inventory(1)
        local item = "coal"
	
        for s = 1, 2 do
            chest_inventory[s].set_stack{name = item, count = game.item_prototypes[item].stack_size}
        end
      end
   end
)
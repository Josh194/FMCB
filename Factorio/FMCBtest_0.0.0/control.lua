script.on_event({defines.events.on_tick},
   function (e)
      if e.tick == 0 then
         game.print("FMCB Tests has been correctly loaded")
      end
   end
)
package main.java;

import main.java.init.ModBlocks;
import main.java.init.ModItems;
import main.java.block.BlockGeneral;
import net.minecraft.block.material.Material;
import net.minecraftforge.fml.common.Mod;
import net.minecraftforge.fml.common.Mod.EventHandler;
import net.minecraftforge.fml.common.event.FMLInitializationEvent;
import net.minecraftforge.fml.common.event.FMLPostInitializationEvent;
import net.minecraftforge.fml.common.event.FMLPreInitializationEvent;

@Mod(modid = "fmcb", useMetadata = true)
public class FMCB {

	@Mod.Instance
	public static FMCB instance;

	@EventHandler
	public void preInit(FMLPreInitializationEvent event) {
		System.out.println("fmcb:preInit");
		//new BlockGeneral(Material.ROCK, "Bruh");
		ModItems.init();
		ModBlocks.init();
	}

	@EventHandler
	public void init(FMLInitializationEvent event) {
		System.out.println("fmcb:Init");
		
	}
	
	@EventHandler
	public void postInit(FMLPostInitializationEvent event) {
		System.out.println("fmcb:postInit");

	}
	
}
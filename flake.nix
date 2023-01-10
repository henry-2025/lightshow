{
	description = "Arduino and avr dev environment";

	outputs = { self, nixpkgs }:
		let pkgs = nixpkgs.legacyPackages.x86_64-linux;
		
	in {
		devShells.x86_64-linux.default = pkgs.mkShell {packages = [
			pkgs.arduino-cli 
				pkgs.cava
				(pkgs.python3.withPackages (p: with p; [pyserial]))
		];
		};
	};

}

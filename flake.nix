{
  description = "Dev environment for light show projects";

  outputs = { self, nixpkgs }:
    let pkgs = nixpkgs.legacyPackages.x86_64-linux;
    in {
      formatter.x86_64-linux = nixpkgs.legacyPackages.x86_64-linux.nixpkgs-fmt;

      devShells.x86_64-linux.default = pkgs.mkShell {
        packages = with pkgs; [
          qt5.wrapQtAppsHook
          makeWrapper
          bashInteractive
          arduino
          (python3.withPackages (p: with p; [
            pyqtgraph
            pyserial
            numpy
            scipy
            pyaudio
          ]))
        ];

        shellHook = ''
                    			bashdir=$(mktemp -d)
                    			makeWrapper "$(type -p bash)" "$bashdir/bash" "''${qtWrapperArgs[@]}"
          								exec "$bashdir/bash"'';
      };
    };

}

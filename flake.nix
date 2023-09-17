{
  description = "Minimal PID controller in C++";

  inputs.nixpkgs.url = "nixpkgs/nixpkgs-unstable";

  outputs = { self, nixpkgs }:
  let
    system = "x86_64-linux";
    pkgs = import nixpkgs { system = system; };
    buildInputs = with pkgs; [ zsh gcc python3 ];
  in
  rec {
    devShells.${system}.default = pkgs.mkShell {
      inherit buildInputs;
      shellHook = ''
        export PYTHONPATH=$PYTHONPATH:$PWD
        exec zsh
      '';
    };

    packages.${system}.default = pkgs.stdenv.mkDerivation {
      inherit buildInputs;
      src = self;
      name = "pid";
      buildPhase = ''
        g++ examples/example.cpp -o example
      '';
      installPhase = ''
        mkdir $out
        install -m +x -t $out example examples/example.py
      '';
    };
  };
}

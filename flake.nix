{
  description = "Minimal PID controller for C++";

  inputs.nixpkgs.url = "nixpkgs/nixpkgs-unstable";

  outputs = { self, nixpkgs }:
  let
    system = "x86_64-linux";

    pkgs = import nixpkgs { system = system; };
  in
  {
    packages.${system}.default = pkgs.stdenv.mkDerivation {

      src = self;

      name = "pid";

			buildInputs = [ pkgs.gcc ];

      buildPhase = "g++ -o example example.cpp";

      installPhase = "mkdir $out && cp example $out";
    };
  };
}

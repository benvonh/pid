{
  description = "Minimal PID controller for C++";

  inputs.nixpkgs.url = "nixpkgs/nixpkgs-unstable";

  outputs = { self, pkgs }:
  {
    packages.x86_64-linux.default = pkgs.stdenv.mkDerivation {

      src = self;

      name = "pid";

      buildInputs = [ pkgs.gcc ];

      buildPhase = "g++ -o example example.cpp";

      installPhase = "mkdir $out && cp example $out";
    };
  };
}

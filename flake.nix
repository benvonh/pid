{
  description = "Minimal PID controller in C++";

  inputs.nixpkgs.url = "nixpkgs/nixpkgs-unstable";

  outputs = { self, nixpkgs }:
  let
    dir = builtins.toString ./.;

    pkgs = import nixpkgs { system = "x86_64-linux"; };

    buildInputs = [ pkgs.gcc ];
  in
  rec {
    devShells.x86_64-linux.default = pkgs.mkShell {
      inherit buildInputs;
    };

    packages.x86_64-linux.default = pkgs.stdenv.mkDerivation {
      inherit buildInputs;

      src = self;
      name = "pid";
      buildPhase = ''
        make
      '';
      installPhase = ''
        mkdir -p $out/bin
        install -t $out/bin example
      '';
    };
  };
}

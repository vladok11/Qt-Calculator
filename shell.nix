{ pkgs ? import <nixpkgs> {} }:
pkgs.mkShell {
  buildInputs = with pkgs; [
    cmake ninja gcc qt6.qtbase qt6.qttools
  ];
}

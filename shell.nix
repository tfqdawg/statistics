{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell{
	nativeBuildInputs = with pkgs; [
		gnuplot
	];

	buildInputs = with pkgs; [
		gsl
	];
}

{ nixpkgs ? import <nixpkgs> {  } }:
with nixpkgs; stdenv.mkDerivation {
	name = "cursorsd";

	enableParallelBuilding = true;

	src = fetchGit {
		url = ./.;
		submodules = true;
	};

	buildInputs = [
		openssl
		zlib
	];

	patchPhase = ''
		pushd uWebSockets
		patch -p1 --forward --input=../uWebSockets-unix-sockets.patch || true
		popd
	'';

	installPhase = ''
		install -TD out $out/bin/cursorsd
	'';

	meta = {
		description = "Unofficial server for the http://cursors.io client.";
		homepage = "https://cursors.uvias.com/";
		platforms = lib.platforms.linux;
	};
}

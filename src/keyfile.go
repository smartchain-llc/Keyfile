package encryptionkey

import (
	"errors"
	"fmt"
	"math/rand"
	"os"
	"path/filepath"
	"regexp"
)

const (
	MAX_KEY_SIZE = 4096
	MIN_KEY_SIZE = 128
)

var defaultPath = fmt.Sprintf("/tmp/%s", keyfileName)
var keyfileName = fmt.Sprintf(".%d.key", os.Getuid())

type KEYY struct {
	size int
	key  []byte
	path string
	info os.FileInfo
}
type Keyer interface {
	IsValid() bool
	GenerateKey() KEYY
	SetPath(string) error
}

func LoadKey() (KEYY, error) {
	var err error
	var k KEYY

	k.path = os.Getenv("EKEY")

	if k.path == "" {
		return KEYY{}, errors.New("No EKEY var or default keys exist. Generate a keyfile with: -keygen <dirpath>")
	}

	var keyFile *os.File
	keyFile, err = os.Open(k.path)
	if err != nil {
		if os.IsNotExist(err) {
			return KEYY{}, errors.New("No EKEY var or default keys exist. Generate a keyfile with: -keygen <dirpath>")
		}
		if os.IsPermission(err) {
			return KEYY{}, errors.New("No valid permissions for using the keyfile.")
		}
		return KEYY{}, err
	}
	defer keyFile.Close()

	k.key = make([]byte, MAX_KEY_SIZE)
	k.size, err = keyFile.Read(k.key)
	k.key = k.key[:k.size]

	if err != nil {
		if os.IsPermission(err) {
			return KEYY{}, errors.New("No valid permissions for using the keyfile.")
		}
		return KEYY{}, err
	}

	return k, err
}

func GenerateKey(dstPath *string) (KEYY, error) {
	var ret KEYY
	var err error

	err = ret.setPath(dstPath)
	if err != nil {
		return KEYY{}, err
	}

	ret.generateKey()

	return ret, err
}

func (k *KEYY) generateKey() {
	var err error

	outfile, err := os.OpenFile(k.path, os.O_CREATE|os.O_RDWR, 0600)
	defer outfile.Close()

	k.size = MAX_KEY_SIZE
	k.key = make([]byte, k.size)

	for i := 0; i < k.size; i++ {
		k.key[i] = byte(rand.Uint32() % 255)
	}

	err = os.WriteFile(k.path, k.key, 0600)
	if err != nil {
		fmt.Println(err)
		os.Exit(12)
	}
	_, werr := outfile.Write(k.key)
	if werr != nil {
		fmt.Println(werr)
		os.Exit(12)
	}
}

func (k *KEYY) setPath(dstPath *string) error {
	var err error

	if *dstPath == defaultPath || *dstPath == "default" {
		k.info, err = os.Stat(fmt.Sprintf("/tmp/.%d.key", os.Getuid()))
		if os.IsPermission(err) {
			return errors.New("Invalid permissions while generating a key in /tmp")
		}
		if os.IsNotExist(err) {
			k.path = defaultPath
			return nil
		}

		if k.info != nil {
			return errors.New("Temporary keyfile already exists. Move and setup EKEY env variable.")
		}
		if err != nil {
			return err
		}

		k.path = defaultPath
	} else {
		if !filepath.IsAbs(*dstPath) {
			return errors.New("Keyfile path must be absolute")
		}

		toFile, _ := regexp.MatchString(".*"+keyfileName, *dstPath)
		if !toFile {
			*dstPath += "/" + keyfileName
		}

		k.info, err = os.Stat(*dstPath)
		if os.IsPermission(err) {
			return errors.New("Invalid permissions while generating a key in /tmp")
		}
		if os.IsNotExist(err) {
			k.path = *dstPath
			return nil
		}
		if k.info != nil {
			return errors.New(fmt.Sprintf("Keyfile for this user already exists"))
		}
	}

	return err
}

func (k KEYY) At(pos int) byte {
	return k.key[pos]
}
func (k KEYY) Size() int {
	return k.size
}

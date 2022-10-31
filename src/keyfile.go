package encryptionkey

import (
	"errors"
	"fmt"
	"math/rand"
	"os"
	"path/filepath"
	"strconv"
)

const (
	MAX_KEY_SIZE = 4096
	MIN_KEY_SIZE = 128
)

var defaultPath = fmt.Sprintf("/tmp/.%d.key", os.Getuid())

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
	uid := strconv.Itoa(os.Getuid())
	k.path = os.Getenv("")
	fmt.Println(k.path)
	if k.path == "" {
		k.path = fmt.Sprintf("", uid)
		k.info, err = os.Stat(k.path)
		if err != nil {
			if os.IsNotExist(err) {
				fmt.Println("No FE_KEY or default keys exist. Generate a keyfile with: fe -g <filepath>")
				os.Exit(1)
			}
			if os.IsPermission(err) {
				fmt.Println("No valid permissions for using the keyfile.")
				os.Exit(1)
			}
			os.Exit(1)
		}
		os.Setenv("", k.path)
	}
	fmt.Println(k.path)
	var keyFile *os.File
	keyFile, err = os.Open(k.path)
	if err != nil {
		if os.IsNotExist(err) {
			fmt.Println("No FE_KEY or default keys exist. Generate a keyfile with: fe -g <filepath>")
			os.Exit(2)
		}
		if os.IsPermission(err) {
			fmt.Println("No valid permissions for using the keyfile.")
			os.Exit(2)
		}
		os.Exit(2)
	}
	defer keyFile.Close()

	k.size, err = keyFile.Read(k.key)
	if err != nil {
		if os.IsNotExist(err) {
			fmt.Println("No FE_KEY or default keys exist. Generate a keyfile with: fe -g <filepath>")
			os.Exit(3)
		}
		if os.IsPermission(err) {
			fmt.Println("No valid permissions for using the keyfile.")
			os.Exit(3)
		}
		os.Exit(3)
	}
	fmt.Println(k.key)

	return k, err
}

func GenerateKey(dstPath *string) (KEYY, error) {
	var ret KEYY
	var err error

	fmt.Printf("%p\n", &ret)
	err = ret.setPath(dstPath)
	ret.generateKey()

	return ret, err
}

func (k *KEYY) generateKey() {
	var err error
	fmt.Printf("%p\n", &k)
	outfile, err := os.OpenFile(k.path, os.O_CREATE|os.O_RDWR, 0600)
	if os.IsPermission(err) || os.IsExist(err) {
		fmt.Println("Cannot generate key a specified filepath")
		os.Exit(11)
	}

	k.size = MAX_KEY_SIZE
	k.key = make([]byte, k.size)

	for i := 0; i < k.size; i++ {
		k.key[i] = byte(rand.Uint32() % 255)
	}
	fmt.Println(k.path)
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
	fmt.Printf("%p\n", &k)
	if *dstPath == "default" {
		k.path = defaultPath
	} else {
		if !filepath.IsAbs(*dstPath) {
			err = errors.New("Keyfile path must be absolute")
		}
		k.path = *dstPath
	}

	return err
}

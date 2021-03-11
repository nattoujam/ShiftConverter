# ShiftConverter
- Linuxでも、左右シフト同時押しでIMEを切り替える
- ユーザー権限で実行する必要があります

# Requirement
- fcitx-mozc

# Usage
1. ``$ install.sh [install dir]``
2. inputグループへ追加
  - ``sudo gpasswd -a [username] input``
3. serviceを起動
  - ``systemctl --user start shiftConverter.servic``

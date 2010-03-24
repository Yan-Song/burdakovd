using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Nakamar;
using Plugins.AccountManager;
using Plugins.Properties;
using System.IO;
using System.Windows.Forms;
using Util;

namespace Plugins
{
    public class WoWStartManager : Loader
    {
        static bool showConfirmationWindow = true;

        public override string WhyShouldNotStartWoW()
        {
            string result;
            bool ready = false;

            do
            {
                result = Manager.GetBestProfile();

                if (showConfirmationWindow)
                {
                    // показать его пользователю
                    var f = new CountDown();

                    if (string.IsNullOrEmpty(result))
                    {
                        f.SetText(new string[] {
                            "Не найден ни один профиль, подходящий для ботерства.", 
                            "Возможно профили не настроены, или же при предыдущем запуске происходили ошибки.",
                            "Или все профили уже ботали достаточное время.",
                            "В любом случае для управления профилями и настройками можно нажать кнопку \"Параметры...\"",
                            "Если нажать 'ОК', то бот не будет работать пока ситуация не изменится" 
                        } );
                    }
                    else
                    {
                        f.SetText(new string[] {
                            string.Format("Автоматически был выбран профиль \"{0}\"", result), 
                            "Если нажать 'ОК', то бот будет использовать этот профиль",
                            "В любом случае для управления профилями и настройками можно нажать кнопку \"Параметры...\""
                        });
                    }

                    f.ShowDialog();

                    showConfirmationWindow = !f.doNotShowThisWindow.Checked;

                    // если пользователь недоволен и изменил настройки, то нужно продолжать цикл
                    ready = !f.SettingsModified;
                }
                else
                {
                    ready = true;
                }
            }
            while(!ready);

            Settings.Default.CurrentProfile = result;
            Settings.Default.Save();

            // теперь в result окончательный результат
            if (string.IsNullOrEmpty(result))
            {
                return "Не найден подходящий профиль";
            }
            else
            {
                return null;
            }
        }

        public override void PrepareForStartWoW()
        {
            Log(string.Format("Использую профиль \"{0}\"", Settings.Default.CurrentProfile));
            
            while (!File.Exists(Settings.Default.ConfigWTF))
            {
                var d = new OpenFileDialog();
                d.Title = "Выберите файл Config.WTF, он находится в поддиректории WTF директории WoW";
                if (d.ShowDialog() == DialogResult.OK)
                {
                    Settings.Default.ConfigWTF = d.FileName;
                    Settings.Default.Save();
                }
            }

            Profile profile = Settings.Default.Profiles[Settings.Default.CurrentProfile];

            ConfigWTF wtf = new ConfigWTF();
            wtf.Load(Settings.Default.ConfigWTF);

            wtf["accountName"] = profile.AccountName;
            wtf["realmName"] = profile.Realm;
            wtf["lastCharacterIndex"] = profile.CharacterIndex.ToString();
            wtf["checkAddonVersion"] = "0"; // чтобы можно было использовать устаревшие аддоны
            wtf["readEULA"] = "1";
            wtf["readScanning"] = "1";
            wtf["readTOS"] = "1";


            wtf.Save();

        }
    }
}

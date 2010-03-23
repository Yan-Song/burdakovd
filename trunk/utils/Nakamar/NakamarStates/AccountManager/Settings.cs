using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Plugins.Properties
{
    
    // Этот класс позволяет обрабатывать определенные события в классе параметров:
    //  Событие SettingChanging возникает перед изменением значения параметра.
    //  Событие PropertyChanged возникает после изменения значения параметра.
    //  Событие SettingsLoaded возникает после загрузки значений параметров.
    //  Событие SettingsSaving возникает перед сохранением значений параметров.
    internal sealed partial class Settings {


        [global::System.Configuration.SettingsSerializeAs(System.Configuration.SettingsSerializeAs.Xml)]
        [global::System.Configuration.UserScopedSettingAttribute()]
        [global::System.Configuration.DefaultSettingValueAttribute("")]
        public global::Util.SerializableDictionary<global::System.String, global::Plugins.AccountManager.Profile> Profiles
        {
            get
            {
                return ((global::Util.SerializableDictionary<global::System.String, global::Plugins.AccountManager.Profile>)(this["Profiles"]));
            }
            set
            {
                this["Profiles"] = value;
            }
        }

        public Settings() {
            // // Для добавления обработчиков событий для сохранения и изменения параметров раскомментируйте приведенные ниже строки:
            //
            // this.SettingChanging += this.SettingChangingEventHandler;
            //
            // this.SettingsSaving += this.SettingsSavingEventHandler;
            //
        }
        
        private void SettingChangingEventHandler(object sender, System.Configuration.SettingChangingEventArgs e) {
            // Добавьте здесь код для обработки события SettingChangingEvent.
        }
        
        private void SettingsSavingEventHandler(object sender, System.ComponentModel.CancelEventArgs e) {
            // Добавьте здесь код для обработки события SettingsSaving.
        }
    }
}

using Util;

namespace WLibrary
{
    /// <summary>
    /// ищет последовательность double в памяти, учитывая что они располагаются не подряд,
    /// а с промежутком в 8 байт на служебную информацию lua
    /// также учитывает что значения гарантировано находятся по адресу кратному 8
    /// http://www.mmowned.com/forums/wow-memory-editing/108898-memory-reading-chat-w-help-add.html
    /// </summary>
    public interface AddonSignatureManager
    {
        /// <summary>
        /// Особенность этого метода в том, что если данных в кэше нет, или они устарели - то возвращается 0,
        /// вместо того чтобы запускать потенциально долгий поиск.
        /// </summary>
        /// <param name="signature"></param>
        /// <returns></returns>
        uint Cached(EquatableList<double> signature);

        /// <summary>
        /// В случае отсутствия или недействительности данных в кэше данный метод может выполняться довольно долго, например минуту.
        /// После выполнения возвращаемое значение записывается в кэш.
        /// </summary>
        /// <param name="signature"></param>
        /// <returns></returns>
        uint Search(EquatableList<double> signature);

        void ClearCache();
    }
}

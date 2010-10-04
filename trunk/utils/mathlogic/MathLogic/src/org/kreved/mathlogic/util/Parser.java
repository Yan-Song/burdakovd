package org.kreved.mathlogic.util;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Set;

import org.kreved.mathlogic.base.AtomicFormula;
import org.kreved.mathlogic.base.CompoundTerm;
import org.kreved.mathlogic.base.Conjunction;
import org.kreved.mathlogic.base.Constant;
import org.kreved.mathlogic.base.Disjunction;
import org.kreved.mathlogic.base.ExistsSuch;
import org.kreved.mathlogic.base.ForAny;
import org.kreved.mathlogic.base.Formula;
import org.kreved.mathlogic.base.FunctionalSymbol;
import org.kreved.mathlogic.base.Implication;
import org.kreved.mathlogic.base.Negation;
import org.kreved.mathlogic.base.PredicateSymbol;
import org.kreved.mathlogic.base.Term;
import org.kreved.mathlogic.base.Variable;

/**
 * @author burdakovd
 * 
 */
public final class Parser {

    /**
     * 
     * @author burdakovd
     * 
     */
    public interface ConstantMatcher {

        /**
         * Определяет по имени, константа ли это или переменная.
         * 
         * @param name
         *            имя
         * @return <code>true</code>, если это имя константы
         */
        boolean isConstant(String name);
    }

    /**
     * Задание списка констант с помощью конечного множества.
     * 
     * @author burdakovd
     * 
     */
    public static final class FiniteMatcher implements ConstantMatcher {
        /**
         * Набор имён констант.
         */
        private final Set<String> constants;

        /**
         * @param constants
         *            набор имён констант
         */
        public FiniteMatcher(final Set<String> constants) {
            this.constants = constants;
        }

        /*
         * (non-Javadoc)
         * 
         * @see
         * org.kreved.mathlogic.util.Parser.ConstantMatcher#isConstant(java.
         * lang.String)
         */
        @Override
        public boolean isConstant(final String name) {
            return constants.contains(name);
        }
    }

    /**
     * Задание набора констант с помощью префикса.
     * 
     * @author burdakovd
     * 
     */
    public static final class PrefixMatcher implements ConstantMatcher {
        /**
         * Префикс. Если имя начинается с него, то это имя константы.
         */
        private final String prefix;

        /**
         * @param prefix
         *            префикс. Если имя начинается с него, то это имя константы.
         */
        public PrefixMatcher(final String prefix) {
            this.prefix = prefix;
        }

        /*
         * (non-Javadoc)
         * 
         * @see
         * org.kreved.mathlogic.util.Parser.ConstantMatcher#isConstant(java.
         * lang.String)
         */
        @Override
        public boolean isConstant(final String name) {
            return name.startsWith(prefix);
        }
    }

    /**
     * 
     */
    private static final PrefixMatcher DEFAULT_CONSTANT_MATCHER = new PrefixMatcher("c");

    /**
     * Создаёт формулу из строки. Константами считаются символы, начинающиеся с
     * латинской "c".
     * 
     * @param input
     *            входная строка
     * @return формула, полученная из входной строки
     */
    public static Formula parseFormula(final String input) {
        return parseFormula(input, DEFAULT_CONSTANT_MATCHER);
    }

    /**
     * 
     * @param input
     *            входная строка
     * @param matcher
     *            набор констант
     * @return формула, полученная из входной строки
     */
    public static Formula parseFormula(final String input, final ConstantMatcher matcher) {

        final Parser parser = new Parser(input, matcher);

        final Formula ans = parser.nextFormula();

        if (parser.hasTokens()) {
            throw new IllegalArgumentException("лишний текст после формулы: '"
                    + parser.getRemainder() + "'");
        }

        return ans;
    }

    /**
     * @param input
     *            входная строка
     * @return терм
     */
    public static Term parseTerm(final String input) {
        return parseTerm(input, DEFAULT_CONSTANT_MATCHER);
    }

    /**
     * @param input
     *            входная строка
     * @param constantMatcher
     *            набор констант
     * @return терм, полученный из входной строки
     */
    public static Term parseTerm(final String input, final ConstantMatcher constantMatcher) {

        final Parser parser = new Parser(input, constantMatcher);

        final Term ans = parser.nextTerm();

        if (parser.hasTokens()) {
            throw new IllegalArgumentException("лишний текст после терма: '"
                    + parser.getRemainder() + "'");
        }

        return ans;
    }

    /**
     * Разбираемая строка.
     */
    private final String input;

    /**
     * Позиция следующего символа в строке.
     */
    private int position;

    /**
     * Список символов импликации.
     */
    private static final List<String> IMPLICATION_SYMBOLS = Collections.unmodifiableList(Arrays
            .asList("->", "=>", "implies", "\\implies"));

    /**
     * Список символов дизъюнкции.
     */
    private static final List<String> DISJUNCTION_SYMBOLS = Collections.unmodifiableList(Arrays
            .asList("V", "v", "or", "||", "|", "OR", "Or", "\\or"));

    /**
     * Список символов конъюнкции.
     */
    private static final List<String> CONJUNCTION_SYMBOLS = Collections.unmodifiableList(Arrays
            .asList("&&", "&", "and", "AND", "And", "\\and"));

    /**
     * Список символов отрицания.
     */
    private static final List<String> NEGATION_SYMBOLS = Collections.unmodifiableList(Arrays
            .asList("!", "~", "not", "NOT", "Not", "\\not"));

    /**
     * Список символов квантора всеобщности.
     */
    private static final List<String> UNIVERSAL_QUANTIFIER_SYMBOLS = Collections
            .unmodifiableList(Arrays.asList("any", "ANY", "Any", "\\any", "\\forall", "forall",
                    "all", "All", "ALL"));

    /**
     * Список символов квантора существования.
     */
    private static final List<String> EXISTANCE_QUANTIFIER_SYMBOLS = Collections
            .unmodifiableList(Arrays.asList("exists", "EXISTS", "Exists", "\\exists"));

    /**
     * Список символов-разделителей аргументов.
     */
    private static final List<String> SEPARATOR_SYMBOLS = Collections.unmodifiableList(Arrays
            .asList(",", ";"));

    /**
     * 
     */
    private final ConstantMatcher constantMatcher;

    /**
     * 
     * @param input
     *            входная строка
     * @param matcher
     *            набор констант
     */
    private Parser(final String input, final ConstantMatcher matcher) {
        this.input = input;
        this.constantMatcher = matcher;
        this.position = 0;

    }

    /**
     * Читает и удаляет из ввода закрывающую скобку.
     * 
     * @throws IllegalArgumentException
     *             если скобка не найдена
     */
    private void closeBrace() {
        if (!tryEatString(")")) {
            throw new IllegalArgumentException("Ожидается закрывающая скобка: '" + getRemainder()
                    + "'");
        }
    }

    /**
     * 
     * @return следующий нерассмотренный символ строки. Из строки он удаляется
     */
    private char eatChar() {
        final char ans = lookChar();
        ++position;
        return ans;
    }

    /**
     * @return неразобранная часть строки
     */
    private String getRemainder() {
        return input.substring(position);
    }

    /**
     * @return есть ли непросмотренные символы
     */
    private boolean hasChar() {
        return position < input.length();
    }

    /**
     * @return остались ли неразобранные токены
     */
    private boolean hasTokens() {
        skipSpaces();
        return hasChar();
    }

    /**
     * @param lookChar
     *            символ
     * @return является ли он алфавитно-цифровым
     */
    private boolean isAlphaNumeric(final char lookChar) {
        return Character.isLetterOrDigit(lookChar);
    }

    /**
     * @return следующий нерассмотренный символ. Из строки он не удаляется.
     */
    private char lookChar() {
        if (hasChar()) {
            return input.charAt(position);
        } else {
            throw new IllegalArgumentException("Неожиданный конец входной строки");
        }
    }

    /**
     * @return строку, состоящую из букв и цифр
     */
    private String nextAlphaNumericString() {

        skipSpaces();

        final StringBuilder ans = new StringBuilder();

        while (hasChar() && isAlphaNumeric(lookChar())) {
            ans.append(eatChar());
        }

        return ans.toString();
    }

    /**
     * Читает разделенный запятой список параметров. Признаком конца является
     * закрывающая скобка, которая не удаляется из потока.
     * 
     * @return список термов
     */
    private List<Term> nextArguments() {

        skipSpaces();

        if (lookChar() == ')') {
            return Collections.emptyList();
        } else {
            final List<Term> ans = new ArrayList<Term>();

            while (true) {
                ans.add(nextTerm());

                if (!tryEatOneOf(SEPARATOR_SYMBOLS)) {
                    break;
                }
            }

            return Collections.unmodifiableList(ans);
        }
    }

    /**
     * @return следующую закрытую формулу
     */
    private Formula nextClosedFormula() {

        if (tryEatString("(")) {
            // первый случай: формула в скобках
            final Formula inner = nextFormula();
            closeBrace();
            return inner;

        } else if (tryEatOneOf(NEGATION_SYMBOLS)) {
            // второй случай: отрицание
            return new Negation(nextClosedFormula());

        } else if (tryEatOneOf(UNIVERSAL_QUANTIFIER_SYMBOLS)) {
            // третий случай: квантор всеобщности
            final Variable variable = nextVariable();
            return new ForAny(variable, nextClosedFormula());

        } else if (tryEatOneOf(EXISTANCE_QUANTIFIER_SYMBOLS)) {
            // четвёртый случай: квантор существования
            final Variable variable = nextVariable();
            return new ExistsSuch(variable, nextClosedFormula());

        } else {
            // пятый случай: предикат
            final PredicateSymbol symbol = nextPredicateSymbol();

            openBrace();

            final List<Term> arguments = nextArguments();

            closeBrace();

            return new AtomicFormula(symbol, arguments);
        }
    }

    /**
     * @return конъюнкцию
     */
    private Formula nextConjunction() {
        // выше приоритет имеют только унарные операции

        // для рекурсии используем ассоциативность конъюнкции

        // рассматриваем конъюнкцию некоторого числа "закрытых формул"
        // под "закрытыми" сейчас полагаем формулы в скобках или атомарные
        // формулы, возможно предварённые некоторым количеством кванторов и
        // отрицаний

        final Formula firstAtom = nextClosedFormula();

        if (tryEatOneOf(CONJUNCTION_SYMBOLS)) {
            // рекурсивно находим конъюнкцию оставшихся "закрытых" формул
            final Formula tailConjunction = nextConjunction();
            return new Conjunction(firstAtom, tailConjunction);
        } else {
            return firstAtom;
        }
    }

    /**
     * @return дизъюнкцию
     */
    private Formula nextDisjunction() {
        // выше приоритет имеет конъюнкция
        // читаем дизъюнкцию некоторого (не меньше 1) набора конъюнкций
        // дизъюнкция ассоциативна, поэтому можно врубить рекурсию
        final Formula firstConjunction = nextConjunction();

        if (tryEatOneOf(DISJUNCTION_SYMBOLS)) {
            // рекурсивно находим дизъюнкцию оставшихся конъюнктов
            final Formula tailDisjunction = nextDisjunction();
            return new Disjunction(firstConjunction, tailDisjunction);
        } else {
            return firstConjunction;
        }
    }

    /**
     * @return формулу, записанную в входной строке
     */
    private Formula nextFormula() {
        // минимальный приоритет имеет импликация, так что рассматриваем формулу
        // как импликацию
        return nextImplication();
    }

    /**
     * Не нашёл четких правил о лево- или правоассоциативности импликации, так
     * что чтобы не получить неоднозначности разрешается импликация не более чем
     * двух аргументов, то есть формула <code>a -> b -> c</code> невалидна. Если
     * нужно больше, то придётся использовать скобки, например
     * <code>(a -> b) -> c</code> или <code>a -> (b -> c)</code>.
     * 
     * @return импликацию
     */
    private Formula nextImplication() {

        // после импликации бОльший приоритет имеет дизъюнкция, так что считаем
        // что у нас импликация двух дизъюнкций, или же просто одна дизъюнкция
        final Formula firstDisjunction = nextDisjunction();

        // если далее идёт символ импликации, то случилась импликация
        if (tryEatOneOf(IMPLICATION_SYMBOLS)) {
            final Formula secondDisjunction = nextDisjunction();
            return new Implication(firstDisjunction, secondDisjunction);
        } else {
            return firstDisjunction;
        }
    }

    /**
     * @return предикатный символ
     */
    private PredicateSymbol nextPredicateSymbol() {
        return new PredicateSymbol(nextAlphaNumericString());
    }

    /**
     * @return терм
     */
    private Term nextTerm() {

        final String name = nextAlphaNumericString();

        skipSpaces();

        if (hasChar() && lookChar() == '(') {
            // это функциональный символ
            openBrace();
            final List<Term> arguments = nextArguments();
            closeBrace();
            return new CompoundTerm(new FunctionalSymbol(name), arguments);
        } else {
            // это переменная или константа
            if (constantMatcher.isConstant(name)) {
                return new Constant(name);
            } else {
                return new Variable(name);
            }
        }
    }

    /**
     * @return переменную
     */
    private Variable nextVariable() {
        return new Variable(nextAlphaNumericString());
    }

    /**
     * Читает и удаляет из ввода открывающую скобку.
     * 
     * @throws IllegalArgumentException
     *             если скобка не найдена.
     */
    private void openBrace() {
        if (!tryEatString("(")) {
            throw new IllegalArgumentException("Ожидается открывающая скобка: '" + getRemainder()
                    + "'");
        }
    }

    /**
     * 
     */
    private void skipSpaces() {
        while (hasChar() && lookChar() == ' ') {
            eatChar();
        }
    }

    /**
     * Пытается прочитать в входной строке один из заданных токенов. Если
     * подходят несколько, то первый из них.
     * 
     * @param candidates
     *            список подходящих токенов
     * @return <code>true</code>, если удалось
     */
    private boolean tryEatOneOf(final List<String> candidates) {

        for (final String candidate : candidates) {
            if (tryEatString(candidate)) {
                return true;
            }
        }

        return false;
    }

    /**
     * @param candidate
     *            искомая строка
     * @return удалось ли прочитать с входного потока заданную строку
     */
    private boolean tryEatString(final String candidate) {

        skipSpaces();

        if (input.startsWith(candidate, position)) {
            position += candidate.length();
            return true;
        }

        return false;
    }
}

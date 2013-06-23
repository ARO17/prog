;; Fichier de configuration d'Emacs (Editeur de texte)
;; Le fichier doit s'appeler ~/.emacs ou ~/.emacs.el
;; ENSIMAG 2008.
 
;; Auteur : Matthieu Moy <Matthieu.Moy@imag.fr>
 
;; Ceci est le fichier de configuration d'Emacs. Il est écrit dans un
;; langage appelé Emacs-lisp, mais rassurez-vous, vous n'avez pas
;; besoin de le connaitre pour changer votre configuration.
;;
;; Tout ce qui est précédé par un point-virgule est un commentaire.
 
;; Taille de la fenêtre au démarrage
(if window-system
    (progn
      (set-frame-size (selected-frame) 140 50)
      (set-frame-position (selected-frame) 50 250)))

;; Correspondance des parenthèses :
;; Avec ceci, positionnez le curseur sur une parenthèse ouvrante ou
;; une parenthèse fermante, Emacs met en couleur la paire de
;; parenthèses.
(show-paren-mode t)
 
;; Utiliser UTF-8 comme codage de caractères par défaut.
;; Pour les détails, cf. http://www-verimag.imag.fr/~moy/emacs/#accents
(set-language-environment 'utf-8)
(set-terminal-coding-system 'utf-8)
(set-keyboard-coding-system 'utf-8)
 
;; Afficher les numéros de lignes dans la mode-line (barre du bas de
;; fenêtre) :
(line-number-mode t)
(column-number-mode t)
 
;; Faire clignoter l'écran au lieu de faire « beep ». Sympa en salle
;; TX !
(setq visible-bell t)
 
;; Pour les curieux ...
 
;; La suite de ce fichier ne contient que des commentaires !
;; Ce sont des suggestions pour vous constituer votre
;; .emacs.el. Décommentez les lignes de configuration pour les
;; activer.
 
;; Ne pas afficher le message d'accueil
(setq inhibit-startup-message t)
(setq make-backup-files         nil) ; Don't want any backup files
(setq auto-save-list-file-name  nil) ; Don't want any .saves files
(setq auto-save-default         nil) ; Don't want any auto saving 

;; Switcher entre le buffer courant et le buffer précédemment utilisé
(global-set-key [C-tab] (lambda ()
			   (interactive)
			   (switch-to-buffer (other-buffer))))

;; Se limiter à des lignes de 80 caractères dans les modes textes (y
;; compris le mode LaTeX) :
;; cf. http://www-verimag.imag.fr/~moy/emacs/#autofill
(add-hook 'text-mode-hook 'turn-on-auto-fill)
 
;; Changer le comportement de la selection de fichiers (C-x C-f)
;(ido-mode 1)
 
;; Dans la même série : changer le comportement de la complétion.
(icomplete-mode)
 
;; Pour une interface graphique un peu dépouillée
;(menu-bar-mode -1)
;(scroll-bar-mode -1)
(tool-bar-mode -1)
;(blink-cursor-mode -1)
 
;; Définir des touches pour se déplacer rapidement :
;; Aller à la parenthèse ouvrante correspondante :
(global-set-key [M-right] 'forward-sexp) 
;; Aller à la parenthèse Fermante correspondante :
(global-set-key [M-left] 'backward-sexp) 
 
;;------------------------------------------------------------------------------
;; Find word under cursor with 'F3' key
(require 'etags) ;; provides `find-tag-default' in Emacs 21.
  
  (defun isearch-yank-regexp (regexp)
    "Pull REGEXP into search regexp." 
    (let ((isearch-regexp nil)) ;; Dynamic binding of global.
      (isearch-yank-string regexp))
    (isearch-search-and-update))
  
  (defun isearch-yank-symbol (&optional partialp)
    "Put symbol at current point into search string.
  
  If PARTIALP is non-nil, find all partial matches."
    (interactive "P")
    (let* ((sym (find-tag-default))
	   ;; Use call of `re-search-forward' by `find-tag-default' to
	   ;; retrieve the end point of the symbol.
	   (sym-end (match-end 0))
	   (sym-start (- sym-end (length sym))))
      (if (null sym)
	  (message "No symbol at point")
	(goto-char sym-start)
	;; For consistent behavior, restart Isearch from starting point
	;; (or end point if using `isearch-backward') of symbol.
	(isearch-search)
	(if partialp
	    (isearch-yank-string sym)
	  (isearch-yank-regexp
	   (concat "\\_<" (regexp-quote sym) "\\_>"))))))
  
  (defun isearch-current-symbol (&optional partialp)
    "Incremental search forward with symbol under point.
  
  Prefixed with \\[universal-argument] will find all partial
  matches."
    (interactive "P")
    (let ((start (point)))
      (isearch-forward-regexp nil 1)
      (isearch-yank-symbol partialp)))
  
  (defun isearch-backward-current-symbol (&optional partialp)
    "Incremental search backward with symbol under point.
  
  Prefixed with \\[universal-argument] will find all partial
  matches."
    (interactive "P")
    (let ((start (point)))
      (isearch-backward-regexp nil 1)
      (isearch-yank-symbol partialp)))
  
  (global-set-key [f3] 'isearch-current-symbol)
  (global-set-key [(control f3)] 'isearch-backward-current-symbol)
  
  ;; Subsequent hitting of the keys will increment to the next
  ;; match--duplicating `C-s' and `C-r', respectively.
  (define-key isearch-mode-map [f3] 'isearch-repeat-forward)
  (define-key isearch-mode-map [(control f3)] 'isearch-repeat-backward)


;;------------------------------------------------------------------------------
;; CC mode indentation level to 4
(setq-default c-basic-offset 4)


;;-------------------------------------------------------------------------------
;; Affiche dans la barre des titre le path du fichier ouvert dans le buffer actif
(setq-default frame-title-format
              '(:eval
                (format "%s@%s: %s %s"
                        (or (file-remote-p default-directory 'user)
                            user-real-login-name)
                        (or (file-remote-p default-directory 'host)
                            system-name)
                        (buffer-name)
                        (cond 
                         (buffer-file-truename
                          (concat "(" buffer-file-truename ")"))
                         (dired-directory
                          (concat "{" dired-directory "}"))
                         (t
                          "[no file]")))))


;;-------------------------------------------------------------------------------
;; Template lors de la création d'un fichier de code

;; Variables for template header
(setq user-full-name "Harold André")
(setq user-email-address "harold.andre@scentys.com")

;; On exécute la commande auto-insert à l'ouverture d'un fichier
(add-hook 'find-file-hooks 'auto-insert)
;; Charge la bibliothèque autoinsert qui déclare la liste
;; auto-insert-alist
(load-library "autoinsert")
;;(add-to-list 'load-path "~/.emacs.d/auto-insert-mode/")
;;(load-library "src_file_template")
(load-file "~/.emacs.d/auto-insert-mode/src_file_template.el")
(setq auto-insert-alist
      (append '(((c-mode .  "C Mode") . std-file-header))
	      auto-insert-alist))

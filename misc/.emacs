;;disable splash screen and startup message
(setq inhibit-startup-message t)
(setq initial-scratch-message nil)

;;enable syntax highlight by default
(global-font-lock-mode t)
(setq font-lock-maximum-decoration t)

;;;Uncomment the following line if there is a problem in your .emacs
;;;and then run emacs. The debugger will pop-up at the line with the
;;;error.  
;(setq debug-on-error t)

;(setq scroll-step 1)			   ; scroll 1 line at a time

;;;Emacs 21 only-- disable fancy stuff
(tool-bar-mode 0)			       ; disable toolbar
;;(menu-bar-mode -1)			       ; disable menu-bar
;;(scroll-bar-mode -1)                         ;disable scroll-bar

;; les BEEP sont remplaces par un effet visuel
(setq visible-bell t)

;; Affiche numero de ligne et colonne dans la barre d'info
(setq column-number-mode t)
(setq line-number-mode t)

;; affiche le nom du buffer dans la description de la fenetre
(setq frame-title-format '(buffer-file-name "Emacs: %b (%f)" "Emacs: %b"))

;; parenthese matching
(show-paren-mode 1)
(setq-default hilight-paren-expression t)

;; affichage de l heure dans la barre d'info (format 24h)
(display-time)
(setq display-time-24hr-format t)

;; petite fenetre de compil, pas tout l'ecran, merci
(setq compilation-window-height 10)

;; cacher le buffer de compilation s'il n'y a pas d'erreur
;(defun notify-compilation-result(buffer msg)
;"Notify that the compilation is finished,
;close the *compilation* buffer if the compilation is successful,
;and set the focus back to Emacs frame"
;(if (string-match "^finished" msg)
;(progn
;(delete-windows-on buffer)
;;(tooltip-show "\n Compilation Successful :-) \n "))
;)
;;(tooltip-show "\n Compilation Failed :-( \n "))
;)
;(setq current-frame (car (car (cdr (current-frame-configuration)))))
;(select-frame-set-input-focus current-frame)
;)
;(add-to-list 'compilation-finish-functions
;'notify-compilation-result)

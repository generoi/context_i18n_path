<?php

/**
 * Expose i18n paths as a context condition.
 * @see context_condition_path.inc
 */
class context_i18n_path_condition extends context_condition_path {
  /**
   * Execute.
   */
  function execute() {
    if ($this->condition_used()) {
    // Only use the normal path for matching unlike context_condition_path
      $current_path = array(drupal_get_path_alias($_GET['q']));
      if ($current_path[0] != $_GET['q']) {
        $current_path[] = $_GET['q'];
      }
      // Also add the translated paths
      foreach (translation_path_get_translations($_GET['q']) as $path) {
        if (!in_array($path, $current_path)) {
          $current_path[] = $path;
        }
      }
      foreach ($this->get_contexts() as $context) {
        $paths = $this->fetch_from_context($context, 'values');
        if ($this->match($current_path, $paths, TRUE)) {
          $this->condition_met($context);
        }
      }
    }
  }
}
